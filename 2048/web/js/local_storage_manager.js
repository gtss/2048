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
    var startIndexWithOffset = startIndex + offset;
    var endIndex = location.search.indexOf("&", startIndexWithOffset);
    if(endIndex < 0 && startIndexWithOffset == location.search.length
       || startIndexWithOffset == endIndex ){
        return null;
    }
    return endIndex < 0 ? location.search.substring(startIndexWithOffset) : location.search.substring(startIndexWithOffset, endIndex);
}

function LocalStorageManager() {
  this.bestScoreKey = "bestScore";
  this.gameStateKey = "gameState";
  this.storage = window.localStorage;
  var bestScore = getParameterByName("bestScore");
  var gameState = getParameterByName("gameState");
  if(bestScore){
    this.storage.setItem(this.bestScoreKey, bestScore);
    this.storage.setItem(this.gameStateKey, decodeURIComponent(gameState));
  }
}

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
