using System;
using System.Text.Json.Serialization;

namespace SmartCar.Web
{
    public enum LightStatus
    {
        Open=1,
        Close=0
    }

    public enum MovementDirection:byte
    {
        Passive=0xff,
        FrontLeft= 0x00,
        Front= 0x01,
        FronRight= 0x02,
        AntiClockwise= 0x03,
        Clockwise= 0x04,
        BackLeft= 0x05,
        Back= 0x06,
        BackRight= 0x07
    }
    public class WebDataModel
    {
        [JsonPropertyName("md")]
        public MovementDirection MovementDirection { get; set; }
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
        [JsonPropertyName("pr")]
        public bool ParkActivity { get; set; }
        [JsonPropertyName("hr")]
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
