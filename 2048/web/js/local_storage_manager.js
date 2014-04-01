window.fakeStorage = {
  _data: {},

  setItem: function (id, val) {
    return this._data[id] = String(val);
  },

  getItem: function (id) {
    return this._data.hasOwnProperty(id) ? this._data[id] : undefined;
  },

  removeItem: function (id) {
    return delete this._data[id];
  },

  clear: function () {
    return this._data = {};
  }
};

function getParameterByName(name) {
    var startIndex;
    if(location.search.indexOf("?" + name + "=") == 0){
        startIndex = 0;
    }else{
        startIndex = location.search.indexOf("&" + name + "=");
    }
    if(startIndex < 0){
        return null;
    }
    var offset = name.length + 2;
    var endIndex = location.search.indexOf("&", startIndex + offset);
    return endIndex < 0 ? location.search.substring(startIndex + offset) : location.search.substring(startIndex + offset, endIndex);
}

function LocalStorageManager() {
  this.bestScoreKey     = "bestScore";
  this.gameStateKey     = "gameState";

  var supported = this.localStorageSupported();
  this.storage = supported ? window.localStorage : window.fakeStorage;
  var bestScore = getParameterByName("bestScore");
  var gameState = getParameterByName("gameState");
  if(bestScore && gameState){
    this.storage.setItem(this.bestScoreKey, bestScore);
    this.storage.setItem(this.gameStateKey, decodeURIComponent(gameState));
  }
}

LocalStorageManager.prototype.localStorageSupported = function () {
  var testKey = "test";
  var storage = window.localStorage;

  try {
    storage.setItem(testKey, "1");
    storage.removeItem(testKey);
    return true;
  } catch (error) {
    return false;
  }
};

// Best score getters/setters
LocalStorageManager.prototype.getBestScore = function () {
  return this.storage.getItem(this.bestScoreKey) || 0;
};

LocalStorageManager.prototype.setBestScore = function (score) {
  this.storage.setItem(this.bestScoreKey, score);
};

// Game state getters/setters and clearing
LocalStorageManager.prototype.getGameState = function () {
  var stateJSON = this.storage.getItem(this.gameStateKey);
  return stateJSON ? JSON.parse(stateJSON) : null;
};

LocalStorageManager.prototype.setGameState = function (gameState) {
  this.storage.setItem(this.gameStateKey, JSON.stringify(gameState));
};

LocalStorageManager.prototype.clearGameState = function () {
  this.storage.removeItem(this.gameStateKey);
};
