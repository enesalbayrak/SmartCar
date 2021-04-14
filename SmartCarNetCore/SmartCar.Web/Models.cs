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
        Passive=0,
        FrontLeft= 1,
        Front= 2,
        FronRight= 3,
        AntiClockwise= 4,
        Clockwise= 5,
        BackLeft= 6,
        Back= 7,
        BackRight= 8
    }

    public enum SignalStatus : byte
    {
        Close = 0,
        Left = 1,
        Right = 2,
        Quad = 3
    };

    public class WebDataModel
    {
        [JsonPropertyName("md")]
        public MovementDirection MovementDirection { get; set; }
        [JsonPropertyName("hl")]
        public LightStatus HeadLightStatus { get; set; }
        [JsonPropertyName("bl")]
        public LightStatus BackLightStatus { get; set; }
        [JsonPropertyName("lh")]
        public LightStatus LongHeadLight { get; set; }
        [JsonPropertyName("ss")]
        public SignalStatus SignalStatus { get; set; }
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
