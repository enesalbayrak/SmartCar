using System;
using System.Text.Json.Serialization;

namespace SmartCar.Web
{
    public enum LightStatus
    {
        Open=1,
        Close=0
    }
    public class WebDataModel
    {
        [JsonPropertyName("lmp")]
        public int LeftMotorPower { get; set; }
        [JsonPropertyName("rmp")]
        public int RightMotorPower { get; set; }
        [JsonPropertyName("hl")]
        public LightStatus HeadLightStatus { get; set; }
        [JsonPropertyName("bl")]
        public LightStatus BackLightStatus { get; set; }
        [JsonPropertyName("ls")]
        public LightStatus LeftSignalStatus { get; set; }
        [JsonPropertyName("rs")]
        public LightStatus RightSignalStatus { get; set; }
        [JsonPropertyName("lhl")]
        public LightStatus LongHeadLight { get; set; }
        [JsonPropertyName("qs")]
        public LightStatus QuadSignal { get; set; }
        [JsonPropertyName("prk")]
        public bool ParkActivity { get; set; }
        [JsonPropertyName("hrn")]
        public bool HornActivity { get; set; }
    }

    public class CarDataModel
    {
        [JsonPropertyName("ll")]
        public int LightLevel { get; set; }
        [JsonPropertyName("bp")]
        public int BatteryPower { get; set; }
        [JsonPropertyName("bd")]
        public int BackDistance { get; set; }
        [JsonPropertyName("fd")]
        public int FrontDistance { get; set; }
    }

    public class ConnectionModel
    {
        public string CarKey { get; set; }
        public WebDataModel WebModel { get; set; }
        public CarDataModel CarModel { get; set; }
        public DateTime LastConnectionDate { get; set; }
    }
}
