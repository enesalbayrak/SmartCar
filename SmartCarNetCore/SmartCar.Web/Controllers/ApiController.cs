using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SmartCar.Web.Controllers
{
    [ApiController]
    [Route("/[controller]")]
    public class ApiController : ControllerBase
    {
        private readonly ILogger<ApiController> _logger;

        private static List<ConnectionModel> connections = new List<ConnectionModel>();

        public ApiController(ILogger<ApiController> logger)
        {
            _logger = logger;
        }

        private ConnectionModel CreateCarConnection(string key)
        {
            var connection = new ConnectionModel
            {
                CarKey = key,
                CarModel = new CarDataModel
                {
                    BackDistance = 0,
                    BatteryPower = 0,
                    FrontDistance = 0,
                    LightLevel = 0
                },
                WebModel =
                new WebDataModel
                {
                    MovementDirection = MovementDirection.Passive,
                    BackLightStatus = LightStatus.Close,
                    HeadLightPercent = 0,
                    BackHeadLight=LightStatus.Close,
                    SignalStatus = SignalStatus.Close,
                }
            };
            connections.Add(connection);
            return connection;
        }

        [HttpGet("car")]
        public ActionResult CarConnect([FromHeader(Name = "connection-key")] string key)
        {
            var last = connections.FirstOrDefault(b => b.CarKey == key);
            if (last != null)
                connections.Remove(last);
            CreateCarConnection(key);
            return Ok();
        }

        private CarDataModel controlModel(CarDataModel model,CarDataModel oldModel)
        {
            if (model.BackDistance > 2000)
                model.BackDistance = oldModel.BackDistance;
            if (model.FrontDistance > 2000)
                model.FrontDistance = oldModel.BackDistance;
            return model;
        }

        [HttpPost("car")]
        public ActionResult<WebDataModel> CarRequest([FromBody] CarDataModel model, [FromHeader(Name = "connection-key")] string key)
        {
            var connection = connections.FirstOrDefault(b => b.CarKey == key);
            if (connection == null)
                connection = CreateCarConnection(key);
            model = controlModel(model, connection.CarModel);
            connection.CarModel = model;
            return Ok(connection.WebModel);
        }

        [HttpGet("web")]
        public ActionResult WebConnect([FromHeader(Name = "connection-key")] string key)
        {
            var connection = connections.FirstOrDefault(b => b.CarKey == key);
            if (connection == null)
                return NotFound();

            return Ok();
        }

        [HttpPost("web")]
        public ActionResult<CarDataModel> WebRequest([FromBody] WebDataModel model, [FromHeader(Name = "connection-key")] string key)
        {
            var connection = connections.FirstOrDefault(b => b.CarKey == key);
            if (connection == null)
                return NotFound();
            connection.WebModel = model;
            return Ok(connection.CarModel);
        }
    }
}
