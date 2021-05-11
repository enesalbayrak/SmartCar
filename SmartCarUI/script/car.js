var webStatus = {
  backDistance: 0,
  frontDistance: 0,
  lightLevel: 0,
  batteryPower: 40,
};

var settings = {
  carKey: "12345678",
  nightMaxValue: 30,
  buzzOpen: 5,
  buzz3: 10,
  buzz2: 15,
  buzz1: 20,
  headLightClose: 5,
  headLightOpen: 10,
  headLightLong: 100,
};
if (localStorage.getItem("settings"))
  settings = JSON.parse(localStorage.getItem("settings"));
else localStorage.setItem("settings", JSON.stringify(settings));

document.getElementById("settings").addEventListener("click", () => {
  document.getElementById("ck-input").value = settings.carKey;
  document.getElementById("nmm-input").value = settings.nightMaxValue;
  document.getElementById("bzo-input").value = settings.buzzOpen;
  document.getElementById("bz3-input").value = settings.buzz3;
  document.getElementById("bz2-input").value = settings.buzz2;
  document.getElementById("bz1-input").value = settings.buzz1;
  document.getElementById("hlc-input").value = settings.headLightClose;
  document.getElementById("hlo-input").value = settings.headLightOpen;
  document.getElementById("llh-input").value = settings.headLightLong;
  document.getElementById("settings-panel").classList.add("open");
});

document.getElementById("close-button").addEventListener("click", () => {
  document.getElementById("settings-panel").classList.remove("open");
});

document.getElementById("save-button").addEventListener("click", () => {
  settings.carKey = document.getElementById("ck-input").value;
  settings.nightMaxValue = document.getElementById("nmm-input").value;
  settings.buzzOpen = document.getElementById("bzo-input").value;
  settings.buzz3 = document.getElementById("bz3-input").value;
  settings.buzz2 = document.getElementById("bz2-input").value;
  settings.buzz1 = document.getElementById("bz1-input").value;
  settings.headLightClose = document.getElementById("hlc-input").value;
  settings.headLightOpen = document.getElementById("hlo-input").value;
  settings.headLightLong = document.getElementById("llh-input").value;
  localStorage.setItem("settings", JSON.stringify(settings));
  document.getElementById("settings-panel").classList.add("open");
});

//#region Hasan

function runAndSetInterval(func, time) {
  func();
  return setInterval(func, time);
}

//#endregion

//#region  signal Hasan
var signalValues = {
  status: "CLOSE",
  interval: -1,
  last: false,
};
function setSignalLamp(status) {
  clearInterval(signalValues.interval);
  signalValues.last = false;
  document.getElementById("signal-left-lamp").src = "imgs/signalclose.svg";
  document.getElementById("signal-right-lamp").src = "imgs/signalclose.svg";

  if (status == "LEFT") {
    signalValues.interval = runAndSetInterval(() => {
      if (signalValues.last) {
        signalValues.last = false;
        document.getElementById("signal-left-lamp").src =
          "imgs/signalclose.svg";
        document.getElementById("signal-close-audio").play();
      } else {
        signalValues.last = true;
        document.getElementById("signal-left-lamp").src = "imgs/signalopen.svg";
        document.getElementById("signal-open-audio").play();
      }
    }, 500);
  } else if (status == "RIGHT") {
    signalValues.interval = runAndSetInterval(() => {
      if (signalValues.last) {
        signalValues.last = false;
        document.getElementById("signal-right-lamp").src =
          "imgs/signalclose.svg";
        document.getElementById("signal-close-audio").play();
      } else {
        signalValues.last = true;
        document.getElementById("signal-right-lamp").src =
          "imgs/signalopen.svg";
        document.getElementById("signal-open-audio").play();
      }
    }, 500);
  } else if (status == "QUAD") {
    signalValues.interval = runAndSetInterval(() => {
      if (signalValues.last) {
        signalValues.last = false;
        document.getElementById("signal-left-lamp").src =
          "imgs/signalclose.svg";
        document.getElementById("signal-right-lamp").src =
          "imgs/signalclose.svg";
        document.getElementById("signal-close-audio").play();
      } else {
        signalValues.last = true;
        document.getElementById("signal-left-lamp").src = "imgs/signalopen.svg";
        document.getElementById("signal-right-lamp").src =
          "imgs/signalopen.svg";
        document.getElementById("signal-open-audio").play();
      }
    }, 500);
  } else document.getElementById("signal-close-audio").play();
}

var signalStatus = {
  quad: false,
  signal: "CLOSE",
  getStatusValue: () => {
    if (signalStatus.quad) return 3;
    if (signalStatus.signal == "LEFT") return 1;
    else if (signalStatus.signal == "RIGHT") return 2;
    return 0;
  },
};

function setSignalStatus(status) {
  if (status == "LEFT") {
    signalStatus.signal = "LEFT";
    document.getElementById("signal-left").classList.add("active");
    document.getElementById("signal-right").classList.remove("active");
  } else if (status == "RIGHT") {
    signalStatus.signal = "RIGHT";
    document.getElementById("signal-right").classList.add("active");
    document.getElementById("signal-left").classList.remove("active");
  } else if (status == "QUAD") {
    signalStatus.quad = true;
    document.getElementById("signal-quad").classList.add("active");
  } else if (status == "QUADCLOSE") {
    signalStatus.quad = false;
    document.getElementById("signal-quad").classList.remove("active");
  } else {
    signalStatus.signal = "CLOSE";
    document.getElementById("signal-left").classList.remove("active");
    document.getElementById("signal-right").classList.remove("active");
  }

  setSignalLamp(signalStatus.quad ? "QUAD" : signalStatus.signal);
}

document.getElementById("signal-left").addEventListener("click", () => {
  setSignalStatus(signalStatus.signal == "LEFT" ? "CLOSE" : "LEFT");
});
document.getElementById("signal-right").addEventListener("click", () => {
  setSignalStatus(signalStatus.signal == "RIGHT" ? "CLOSE" : "RIGHT");
});
document.getElementById("signal-close").addEventListener("click", () => {
  setSignalStatus("CLOSE");
});
document.getElementById("signal-quad").addEventListener("click", () => {
  setSignalStatus(signalStatus.quad ? "QUADCLOSE" : "QUAD");
});

document.addEventListener("keydown", (ev) => {
  switch (ev.key.toLowerCase()) {
    case "e":
      setSignalStatus(signalStatus.signal == "LEFT" ? "CLOSE" : "LEFT");
      break;
    case "r":
      setSignalStatus(signalStatus.signal == "RIGHT" ? "CLOSE" : "RIGHT");
      break;
    case "t":
      setSignalStatus("CLOSE");
      break;

    case "o":
      setSignalStatus(signalStatus.quad ? "QUADCLOSE" : "QUAD");
      break;
  }
});
//#endregion

//#region headlight Taner
var headlightStatus = {
  status: "OFF",
  active: false,
  long: false,
  getHeadLightPercent: () => {
    if (!headlightStatus.active) return settings.headLightClose;
    if (headlightStatus.long) return settings.headLightLong;
    return settings.headLightOpen;
  },
};
function setHeadlightStyles() {
  if (headlightStatus.long)
    document.getElementById("headlight-long").classList.add("active");
  else document.getElementById("headlight-long").classList.remove("active");

  if (headlightStatus.long && headlightStatus.active)
    document.getElementById("headlight-long-lamp").src =
      "imgs/headlightLopen.svg";
  else
    document.getElementById("headlight-long-lamp").src =
      "imgs/headlightLclose.svg";
  if (headlightStatus.status == "ON") {
    document.getElementById("headlight-on").classList.add("active");
    document.getElementById("headlight-off").classList.remove("active");
    document.getElementById("headlight-auto").classList.remove("active");
  } else if (headlightStatus.status == "AUTO") {
    document.getElementById("headlight-on").classList.remove("active");
    document.getElementById("headlight-off").classList.remove("active");
    document.getElementById("headlight-auto").classList.add("active");
  } else {
    document.getElementById("headlight-on").classList.remove("active");
    document.getElementById("headlight-off").classList.add("active");
    document.getElementById("headlight-auto").classList.remove("active");
  }

  if (headlightStatus.active)
    document.getElementById("headlight-lamp").src = "imgs/headlightopen.svg";
  else
    document.getElementById("headlight-lamp").src = "imgs/headlightclose.svg";
}
function setLongHeadlight(status) {
  headlightStatus.long = status;
  setHeadlightStyles();
}

function setHeadlight(status) {
  headlightStatus.status = status;
  if (status == "ON") headlightStatus.active = true;
  else if (status == "AUTO" && webStatus.lightLevel <= settings.nightMaxValue)
    headlightStatus.active = true;
  else headlightStatus.active = false;
  setHeadlightStyles();
}

document.getElementById("headlight-long").addEventListener("click", () => {
  setLongHeadlight(!headlightStatus.long);
});

document.getElementById("headlight-on").addEventListener("click", () => {
  setHeadlight("ON");
});
document.getElementById("headlight-off").addEventListener("click", () => {
  setHeadlight("OFF");
});
document.getElementById("headlight-auto").addEventListener("click", () => {
  setHeadlight("AUTO");
});

document.addEventListener("keydown", (ev) => {
  switch (ev.key.toLowerCase()) {
    case "f":
      setHeadlight("ON");
      break;
    case "g":
      setHeadlight("OFF");
      break;
    case "h":
      setHeadlight("AUTO");
      break;
    case "b":
      setLongHeadlight(!headlightStatus.long);
      break;
  }
});

//#endregion

//#region  park Yusuf
var parkStatus = false;
function setParkStatus(status) {
  parkStatus = status;
  if (parkStatus) {
    document.getElementById("park").classList.add("active");
    document.getElementById("park-lamp").src = "imgs/parkingopen.svg";
  } else {
    document.getElementById("park-lamp").src = "imgs/parkingclose.svg";
    document.getElementById("park").classList.remove("active");
  }
}

document.getElementById("park").addEventListener("click", () => {
  setParkStatus(!parkStatus);
});

document.addEventListener("keydown", (ev) => {
  switch (ev.key.toLowerCase()) {
    case "p":
      setParkStatus(!parkStatus);
  }
});

//#endregion

//#region  horn Yusuf
var hornStatus = false;
function setHornStatus(status) {
  hornStatus = status;
  if (hornStatus) {
    document.getElementById("horn").classList.add("active");
  } else {
    document.getElementById("horn").classList.remove("active");
  }
}

document.getElementById("horn").addEventListener("mousedown", () => {
  setHornStatus(true);
});
document.addEventListener("mouseup", () => {
  setHornStatus(false);
});

document.addEventListener("keydown", (ev) => {
  switch (ev.key.toLowerCase()) {
    case "v":
      setHornStatus(true);
  }
});
document.addEventListener("keyup", (ev) => {
  switch (ev.key.toLowerCase()) {
    case "v":
      setHornStatus(false);
  }
});

function getBuzzerStatus() {
  if (hornStatus) return 4;
  if (!parkStatus) return 0;
  var minDistance = Math.min(webStatus.backDistance, webStatus.frontDistance);

  if (minDistance <= settings.buzzOpen) return 4;
  if (minDistance <= settings.buzz3) return 3;
  if (minDistance <= settings.buzz2) return 2;
  if (minDistance <= settings.buzz1) return 1;
  return 0;
}

//#endregion

//#region direction Enes
var directionStatus = {
  front: false,
  back: false,
  left: false,
  right: false,
  position: 0,
};

function setDirectionStyle() {
  if (directionStatus.front && directionStatus.left) {
    document.getElementById("d-lf").classList.add("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 1;
  } else if (directionStatus.front && directionStatus.right) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.add("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 3;
  } else if (directionStatus.back && directionStatus.left) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.add("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 6;
  } else if (directionStatus.back && directionStatus.right) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.add("active");
    directionStatus.position = 8;
  } else if (directionStatus.front) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.add("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 2;
  } else if (directionStatus.left) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.add("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 4;
  } else if (directionStatus.right) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.add("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 5;
  } else if (directionStatus.back) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.add("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 7;
  } else {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
    directionStatus.position = 0;
  }
}
document.addEventListener("keydown", (ev) => {
  switch (ev.key.toLowerCase()) {
    case "arrowup":
    case "w":
      directionStatus.front = true;
      break;
    case "arrowleft":
    case "a":
      directionStatus.left = true;
      break;
    case "arrowdown":
    case "s":
      directionStatus.back = true;
      break;
    case "arrowright":
    case "d":
      directionStatus.right = true;
      break;
  }
  setDirectionStyle();
});

document.addEventListener("keyup", (ev) => {
  switch (ev.key.toLowerCase()) {
    case "arrowup":
    case "w":
      directionStatus.front = false;
      break;
    case "arrowleft":
    case "a":
      directionStatus.left = false;
      break;
    case "arrowdown":
    case "s":
      directionStatus.back = false;
      break;
    case "arrowright":
    case "d":
      directionStatus.right = false;
      break;
  }
  setDirectionStyle();
});

document.getElementById("d-lf").addEventListener("mousedown", () => {
  directionStatus.left = true;
  directionStatus.front = true;
  setDirectionStyle();
});

document.getElementById("d-f").addEventListener("mousedown", () => {
  directionStatus.front = true;
  setDirectionStyle();
});
document.getElementById("d-rf").addEventListener("mousedown", () => {
  directionStatus.right = true;
  directionStatus.front = true;
  setDirectionStyle();
});

document.getElementById("d-l").addEventListener("mousedown", () => {
  directionStatus.left = true;
  setDirectionStyle();
});

document.getElementById("d-r").addEventListener("mousedown", () => {
  directionStatus.right = true;
  setDirectionStyle();
});

document.getElementById("d-lb").addEventListener("mousedown", () => {
  directionStatus.left = true;
  directionStatus.back = true;
  setDirectionStyle();
});

document.getElementById("d-b").addEventListener("mousedown", () => {
  directionStatus.back = true;
  setDirectionStyle();
});

document.getElementById("d-rb").addEventListener("mousedown", () => {
  directionStatus.right = true;
  directionStatus.back = true;
  setDirectionStyle();
});
document.addEventListener("mouseup", () => {
  directionStatus.right = false;
  directionStatus.left = false;
  directionStatus.front = false;
  directionStatus.back = false;
  setDirectionStyle();
});

//#endregion

//#region battery warn
var batteryWarnStatus = false;
document.getElementById("empty-battery").addEventListener("click", () => {
  batteryWarnStatus = !batteryWarnStatus;
  if (batteryWarnStatus)
    document.getElementById("empty-battery").classList.add("active");
  else document.getElementById("empty-battery").classList.remove("active");
});
//#endregion

//#region connection Taner
function bindServerData() {
  document.getElementById("back-distance-value").innerHTML =
    webStatus.backDistance;
  document.getElementById("front-distance-value").innerHTML =
    webStatus.frontDistance;
  setHeadlight(headlightStatus.status);

  document.getElementById("night-lamp").src =
    webStatus.lightLevel > settings.nightMaxValue
      ? "imgs/nightclose.svg"
      : "imgs/nightopen.svg";
  var batteryLevelImage;
  if (webStatus.batteryPower < 10) batteryLevelImage = 0;
  else if (webStatus.batteryPower < 40) batteryLevelImage = 1;
  else if (webStatus.batteryPower < 70) batteryLevelImage = 2;
  else batteryLevelImage = 3;
  document.getElementById("battery-lamb").src =
    "imgs/battery" + batteryLevelImage + ".svg";
}

var active = false;
var connect = async () => {
  if (active) return;
  active = true;
  try {
    var result = await fetch("http://api.kousmartcar.online/api/web", {
      method: "POST",
      headers: {
        "connection-key": settings.carKey,
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        md: directionStatus.position,
        hl: headlightStatus.getHeadLightPercent(),
        bh: headlightStatus.active ? 1 : 0,
        bl: [6, 7, 8].indexOf(directionStatus.position) >= 0 ? 1 : 0,
        ss: batteryWarnStatus ? 4 : signalStatus.getStatusValue(),
        bz: getBuzzerStatus(),
      }),
    });
    result = await result.json();
    webStatus.lightLevel = result.ll;
    webStatus.backDistance = Math.round(result.bd / 10);
    webStatus.frontDistance = Math.round(result.fd / 10);
    webStatus.batteryPower = result.bp;
    bindServerData();
  } catch (error) {
    console.error(error);
  }
  active = false;
};
runAndSetInterval(connect, 50);
//#endregion

//#region Enes
//#endregion
