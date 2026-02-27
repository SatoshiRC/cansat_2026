#include "NMEA.hpp"
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

NMEAProcessor::NMEAProcessor() : referenceSet_(false) {
    referencePoint_.latitude = 0.0;
    referencePoint_.longitude = 0.0;
    referencePoint_.altitude = 0.0;
    referencePoint_.valid = false;
    _isLastFrameValid = false;
}

NMEAProcessor::~NMEAProcessor() {
}

void NMEAProcessor::setReferencePoint(double latitude, double longitude, double altitude) {
    referencePoint_.latitude = latitude;
    referencePoint_.longitude = longitude;
    referencePoint_.altitude = altitude;
    referencePoint_.valid = true;
    referenceSet_ = true;
}

void NMEAProcessor::setReferencePoint(const GPSPosition& reference) {
    referencePoint_ = reference;
    referenceSet_ = reference.valid;
}

void NMEAProcessor::onReceive(const std::vector<uint8_t>& nmeaFrame) {
	if (nmeaFrame.empty() || nmeaFrame[0] != '$') {
        return; // 無効なNMEAフレーム
    }
    
    bool parsed = false;
    
    // uint8_t配列を文字列に変換して判定
    std::string frameStr = vectorToString(nmeaFrame);
    
    // GGAまたはRMCセンテンスをパース
    if (frameStr.find("$GPGGA") == 0 || frameStr.find("$GNGGA") == 0) {
        parsed = parseGGA(nmeaFrame, lastPoint_);
    }
    
    if (parsed && lastPoint_.valid){
    	if(referenceSet_) {
			NEDPosition nedPos = convertToNED(lastPoint_, referencePoint_);

			if (positionCallback_) {
				positionCallback_(nedPos);
			}

    	}else{
    		NEDPosition dummy;
    		dummy.valid = false;
    		positionCallback_(dummy);
    	}
    }
}

void NMEAProcessor::setPositionCallback(std::function<void(const NEDPosition&)> callback) {
    positionCallback_ = callback;
}

GPSPosition NMEAProcessor::getReferencePoint() const {
    return referencePoint_;
}

bool NMEAProcessor::isReferenceSet() const {
    return referenceSet_;
}

bool NMEAProcessor::parseGGA(const std::vector<uint8_t>& sentence, GPSPosition& position) {
    std::string sentenceStr = vectorToString(sentence);
    std::vector<std::string> tokens = splitByComma(sentenceStr);
    
    if (tokens.size() < 15) {
        return false;
    }
    
	// 時刻（tokens[1]）は今回は使用しない

	// 緯度
	if (!tokens[2].empty() && !tokens[3].empty()) {
		double lat = std::stod(tokens[2]);
		position.latitude = convertDMtoDegrees(lat);
		if (tokens[3] == "S") {
			position.latitude = -position.latitude;
		}
	} else {
		return false;
	}

	// 経度
	if (!tokens[4].empty() && !tokens[5].empty()) {
		double lon = std::stod(tokens[4]);
		position.longitude = convertDMtoDegrees(lon);
		if (tokens[5] == "W") {
			position.longitude = -position.longitude;
		}
	} else {
		return false;
	}

	// 品質インジケータ
	int quality = 0;
	if (!tokens[6].empty()) {
		quality = std::stoi(tokens[6]);
	}
    position.valid = quality;

	if (quality == 0) {
		return false;
	}

	// 高度
	if (!tokens[9].empty()) {
		position.altitude = std::stod(tokens[9]);
	} else {
		position.altitude = 0.0;
	}
    
	return true;
}

bool NMEAProcessor::parseRMC(const std::vector<uint8_t>& sentence, GPSPosition& position) {
    std::string sentenceStr = vectorToString(sentence);
    std::vector<std::string> tokens = splitByComma(sentenceStr);
    
    if (tokens.size() < 12) {
        return false;
    }
    
	// ステータス
	if (tokens[2] != "A") {
		position.valid = false;
		return false;
	}

	// 緯度
	if (!tokens[3].empty() && !tokens[4].empty()) {
		double lat = std::stod(tokens[3]);
		position.latitude = convertDMtoDegrees(lat);
		if (tokens[4] == "S") {
			position.latitude = -position.latitude;
		}
	} else {
		return false;
	}

	// 経度
	if (!tokens[5].empty() && !tokens[6].empty()) {
		double lon = std::stod(tokens[5]);
		position.longitude = convertDMtoDegrees(lon);
		if (tokens[6] == "W") {
			position.longitude = -position.longitude;
		}
	} else {
		return false;
	}

	// RMCには高度情報がないため0に設定
	position.altitude = 0.0;
	position.valid = true;
	return true;
}

double NMEAProcessor::convertDMtoDegrees(double dm) {
    int degrees = static_cast<int>(dm / 100);
    double minutes = dm - (degrees * 100);
    return degrees + (minutes / 60.0);
}

NEDPosition NMEAProcessor::convertToNED(const GPSPosition& current, const GPSPosition& reference) {
    NEDPosition ned;
    
    // 緯度・経度の差分をラジアンに変換
    double deltaLat = (current.latitude - reference.latitude) * M_PI / 180.0;
    double deltaLon = (current.longitude - reference.longitude) * M_PI / 180.0;
    double refLatRad = reference.latitude * M_PI / 180.0;
    
    // NED座標に変換
    ned.north = deltaLat * EARTH_RADIUS;
    ned.east = deltaLon * EARTH_RADIUS * cos(refLatRad);
    ned.down = -(current.altitude - reference.altitude); // NEDでは下方向が正
    
    return ned;
}

std::string NMEAProcessor::vectorToString(const std::vector<uint8_t>& data) {
    std::string result;
    result.reserve(data.size());
    for (uint8_t byte : data) {
        result.push_back(static_cast<char>(byte));
    }
    return result;
}

std::vector<std::string> NMEAProcessor::splitByComma(const std::string& str) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    return tokens;
}
