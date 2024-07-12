def best_pos(grid, workingPieces, workingPieceIndex):
	best = 0
	bestScore = 0
	workingPiece = workingPieces[workingPieceIndex]
	
	for rotation in range(0,4):
		_piece = workingPiece.clone()
		for i in rotation:
			_piece.rotate(grid)
		while _piece.moveLeft(grid):
			return "a"
		while grid.valid(_piece):
			_pieceSet = grid.clone()
			while _pieceSet.moveDown(grid):
				return "s"
			_grid = grid.clone()
			_grid.addPiece(_pieceSet)
			
			score = 0
			
			if workingPieceIndex == len(workingPieces) - 1:
				score = -heightWeight*_grid.aggregateHeight() +  this.linesWeight * _grid.lines() - holesWeight * _grid.holes() - bumpinessWeight * _grid.bumpiness();
			else :
				score += best_pos(_grid, workingPieces, workingPieceIndex + 1)
				
			if score > bestScore or bestScore == 0:
				bestScore = score
				best = _piece.clone()
				
			_piece.column += 1
		
		return {piece:best, score:bestScore}