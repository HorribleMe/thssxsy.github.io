describe('drawCell', function(){
	it('should be a function', function(){
		assert.isFunction(drawCell);
	});
	it('should have three arguments', function(){
		assert.equal(drawCell.length, 3);
	})
});

describe('getState', function(){
	it('should be a function', function(){
		assert.isFunction(getState);
	});
	it('should have two arguments', function(){
		assert.equal(getState.length, 2);
	});
	it('should return 0 or 1', function(){
		assert.include([0, 1], getState(33, 33))
	});
	it('should return 1 when a cell has three neighbours', function(){
		cells[0][0] = 0;
		cells[1][0] = 1;
		cells[2][0] = 0;
		cells[2][1] = 0;
		cells[2][2] = 1;
		cells[0][1] = 0;
		cells[0][2] = 1;
		cells[1][2] = 0;
		assert.equal(getState(1, 1), 1);
	});
	it('should stay when a cell has two neighbours', function(){
		var i = cells[1][1];
		cells[0][0] = 0;
		cells[1][0] = 0;
		cells[2][0] = 0;
		cells[2][1] = 0;
		cells[2][2] = 1;
		cells[0][1] = 0;
		cells[0][2] = 1;
		cells[1][2] = 0;
		assert.equal(getState(1, 1), i);
	});
	it('should return 0 when a cell has more than three neighbours', function(){
		cells[0][0] = 1;
		cells[1][0] = 0;
		cells[2][0] = 1;
		cells[2][1] = 0;
		cells[2][2] = 1;
		cells[0][1] = 0;
		cells[0][2] = 1;
		cells[1][2] = 0;
		assert.equal(getState(1, 1), 0);
	});
	it('should return 0 when a cell has less than two neighbours', function(){
		cells[0][0] = 0;
		cells[1][0] = 0;
		cells[2][0] = 1;
		cells[2][1] = 0;
		cells[2][2] = 0;
		cells[0][1] = 0;
		cells[0][2] = 0;
		cells[1][2] = 0;
		assert.equal(getState(1, 1), 0);
	})
});

describe('start', function(){
	it('should be a function', function(){
		assert.isFunction(start);
	});
	it('After this operation startButton should be disabled', function(){
		start();
		assert.equal(startButton.disabled, true);
	});
	it('After this operation pauseButton should be available', function(){
		start();
		assert.equal(pauseButton.disabled, false);
	});
});

describe('pause', function(){
	it('should be a function', function(){
		assert.isFunction(pause);
	});
	it('After this operation resetButton should be available', function(){
		pause();
		assert.equal(resetButton.disabled, false);
	});
});

describe('gameInit', function(){
	it('should be a function', function(){
		assert.isFunction(gameInit);
	});
	it('After this operation resetButton&pauseButton should be disabled', function(){
		gameInit();
		assert.equal(resetButton.disabled, true);
		assert.equal(pauseButton.disabled, true);
	});
});