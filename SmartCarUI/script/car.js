function runAndSetInterval(func, time) {
  func();
  return setInterval(func, time);
}
var webStatus = {
  backDistance: 0,
  frontDistance: 0,
  lightLevel: 40,
};

//#region  signal
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

//#region headlight
var headlightStatus = {
  status: "OFF",
  active: false,
  long: false,
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
  else if (status == "AUTO" && webStatus.lightLevel <= 30)
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

//#region  park
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

//#region  horn
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
document.getElementById("horn").addEventListener("mouseup", () => {
  setHornStatus(false);
});

document.getElementById("horn").addEventListener("mouseleave", () => {
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
//#endregion

//#region direction
var directionStatus = {
  front: false,
  back: false,
  left: false,
  right: false,
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
  } else if (directionStatus.front && directionStatus.right) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.add("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
  } else if (directionStatus.back && directionStatus.left) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.add("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
  } else if (directionStatus.back && directionStatus.right) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.add("active");
  } else if (directionStatus.front) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.add("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
  } else if (directionStatus.left) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.add("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
  } else if (directionStatus.right) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.add("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
  } else if (directionStatus.back) {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.add("active");
    document.getElementById("d-rb").classList.remove("active");
  } else {
    document.getElementById("d-lf").classList.remove("active");
    document.getElementById("d-f").classList.remove("active");
    document.getElementById("d-rf").classList.remove("active");
    document.getElementById("d-l").classList.remove("active");
    document.getElementById("d-r").classList.remove("active");
    document.getElementById("d-lb").classList.remove("active");
    document.getElementById("d-b").classList.remove("active");
    document.getElementById("d-rb").classList.remove("active");
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

document.getElementById("d-lf").addEventListener("mousedown", () => {
  directionStatus.left = true;
  directionStatus.front = true;
  setDirectionStyle();
});
document.getElementById("d-lf").addEventListener("mouseup", () => {
  directionStatus.left = false;
  directionStatus.front = false;
  setDirectionStyle();
});

document.getElementById("d-f").addEventListener("mousedown", () => {
  directionStatus.front = true;
  setDirectionStyle();
});
document.getElementById("d-f").addEventListener("mouseup", () => {
  directionStatus.front = false;
  setDirectionStyle();
});

document.getElementById("d-rf").addEventListener("mousedown", () => {
  directionStatus.right = true;
  directionStatus.front = true;
  setDirectionStyle();
});
document.getElementById("d-rf").addEventListener("mouseup", () => {
  directionStatus.right = false;
  directionStatus.front = false;
  setDirectionStyle();
});

document.getElementById("d-l").addEventListener("mousedown", () => {
  directionStatus.left = true;
  setDirectionStyle();
});
document.getElementById("d-l").addEventListener("mouseup", () => {
  directionStatus.left = false;
  setDirectionStyle();
});

document.getElementById("d-r").addEventListener("mousedown", () => {
  directionStatus.right = true;
  setDirectionStyle();
});
document.getElementById("d-r").addEventListener("mouseup", () => {
  directionStatus.right = false;
  setDirectionStyle();
});

document.getElementById("d-lb").addEventListener("mousedown", () => {
  directionStatus.left = true;
  directionStatus.back = true;
  setDirectionStyle();
});
document.getElementById("d-lb").addEventListener("mouseup", () => {
  directionStatus.left = false;
  directionStatus.back = false;
  setDirectionStyle();
});

document.getElementById("d-b").addEventListener("mousedown", () => {
  directionStatus.back = true;
  setDirectionStyle();
});
document.getElementById("d-b").addEventListener("mouseup", () => {
  directionStatus.back = false;
  setDirectionStyle();
});

document.getElementById("d-rb").addEventListener("mousedown", () => {
  directionStatus.right = true;
  directionStatus.back = true;
  setDirectionStyle();
});
document.getElementById("d-rb").addEventListener("mouseup", () => {
  directionStatus.right = false;
  directionStatus.back = false;
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
//#endregion
