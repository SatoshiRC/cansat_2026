#ifndef NMEA_HPP
#define NMEA_HPP

#include <vector>
#include <functional>
#include <cmath>
#include <cstdint>
#include <string>

struct GPSPosition {
    double latitude;   // 緯度（度）
    double longitude;  // 経度（度）
    double altitude;   // 高度（メートル）
    bool valid;        // データの有効性
};

struct NEDPosition {
    double north;      // 北方向距離（メートル）
    double east;       // 東方向距離（メートル）
    double down;       // 下方向距離（メートル）
};

class NMEAProcessor {
private:
    GPSPosition referencePoint_;  // 基準点
    bool referenceSet_;           // 基準点が設定されているか
    
    // NMEAデータをパースする内部関数
    bool parseGGA(const std::vector<uint8_t>& sentence, GPSPosition& position);
    bool parseRMC(const std::vector<uint8_t>& sentence, GPSPosition& position);
    
    // 度分表記から十進度に変換
    double convertDMtoDegrees(double dm);
    
    // GPS座標をNED座標に変換
    NEDPosition convertToNED(const GPSPosition& current, const GPSPosition& reference);
    
    // uint8_t配列を文字列に変換するヘルパー関数
    std::string vectorToString(const std::vector<uint8_t>& data);
    
    // 文字列をカンマで分割するヘルパー関数
    std::vector<std::string> splitByComma(const std::string& str);
    
    // 地球の半径（メートル）
    static constexpr double EARTH_RADIUS = 6378137.0;

public:
    NMEAProcessor();
    ~NMEAProcessor();
    
    // 基準点を設定
    void setReferencePoint(double latitude, double longitude, double altitude = 0.0);
    void setReferencePoint(const GPSPosition& reference);
    
    // NMEAフレームを受信して処理
    void onReceive(const std::vector<uint8_t>& nmeaFrame);
    bool isLastFrameValid(){
    	return _isLastFrameValid;
    }
    
    // コールバック関数を設定（NEDポジションが更新された時に呼ばれる）
    void setPositionCallback(std::function<void(const NEDPosition&)> callback);
    
    // 現在の基準点を取得
    GPSPosition getReferencePoint() const;
    
    // 基準点が設定されているかチェック
    bool isReferenceSet() const;

private:
    std::function<void(const NEDPosition&)> positionCallback_;
    bool _isLastFrameValid;
};

#endif // NMEA_HPP
