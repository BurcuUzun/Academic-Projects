def solve_tiling(grid_height, grid_width, pieces_list):
    """
    Solves a 2D tiling puzzle using a backtracking algorithm.
    Returns a list of coordinates for each piece or None if no solution exists.
    """
    shapes = {
        # I: Anchor is 1st block. [X][ ][ ][ ]
        'I': [(0, 0), (1, 0), (2, 0), (3, 0)],
        
        # J: Anchor is bottom-right. 
        # Visual: Top-left block, then bottom row of 3.
        # Coords relative to bottom-right (0,0):
        'J': [(0, 0), (-1, 0), (-2, 0), (-2, -1)],
        
        # L: Anchor is bottom-left.
        # Visual: Bottom row of 3, then top-right block.
        # Coords relative to bottom-left (0,0):
        'L': [(0, 0), (1, 0), (2, 0), (2, -1)],
        
        # T: Anchor is top-middle.
        # Visual: Single block on top (anchor), row of 3 below.
        'T': [(0, 0), (-1, 1), (0, 1), (1, 1)],
        
        # O: Anchor is top-left.
        'O': [(0, 0), (1, 0), (0, 1), (1, 1)],
        
        # S: Anchor is bottom-left. Stairs go up-right.
        # Bottom row: (0,0), (1,0). Top row (shifted right): (1,-1), (2,-1).
        'S': [(0, 0), (1, 0), (1, -1), (2, -1)],
        
        # Z: Anchor is bottom-left of the bottom segment. Stairs go up-left.
        # Bottom row: (0,0), (1,0). Top row (shifted left): (-1,-1), (0,-1).
        'Z': [(0, 0), (1, 0), (0, -1), (-1, -1)],
        
        # K: Single block.
        'K': [(0, 0)]
    }

    top_left_offsets = {
        'I': (0, 0),
        'J': (-2, -1), 
        'L': (2, -1),  
        'T': (0, 0),
        'O': (0, 0),
        'S': (1, -1),  
        'Z': (-1, -1), 
        'K': (0, 0)
    }

    grid = [[0 for _ in range(grid_width)] for _ in range(grid_height)]
    pieces_counts = {}

    for p in pieces_list:
        pieces_counts[p] = pieces_counts.get(p, 0) + 1

    placements = {k: [] for k in pieces_counts}

    def find_empty():
       
        for r in range(grid_height):
            for c in range(grid_width):
                if grid[r][c] == 0:
                    return r, c
        return None

    def can_place(piece_type, r_anc, c_anc):
        
        for dx, dy in shapes[piece_type]:
            nr, nc = r_anc + dy, c_anc + dx
           
            if not (0 <= nr < grid_height and 0 <= nc < grid_width):
                return False
          
            if grid[nr][nc] == 1:
                return False
        return True

    def toggle_piece(piece_type, r_anc, c_anc, val):
        
        for dx, dy in shapes[piece_type]:
            grid[r_anc + dy][c_anc + dx] = val

    def backtrack():
       
        target = find_empty()
        
        if target is None:
            return True

        row, col = target  
        available_types = [p for p in pieces_counts if pieces_counts[p] > 0]
        available_types.sort() 

        for p_type in available_types:
            
            tx, ty = top_left_offsets[p_type]
            anc_c = col - tx
            anc_r = row - ty
            
            if can_place(p_type, anc_r, anc_c):

                toggle_piece(p_type, anc_r, anc_c, 1)
                pieces_counts[p_type] -= 1
                placements[p_type].append((p_type, anc_c, anc_r))
                
                if backtrack():
                    return True
                
                placements[p_type].pop()
                pieces_counts[p_type] += 1
                toggle_piece(p_type, anc_r, anc_c, 0)

        return False

    if backtrack():
        
        result = []
        temp_placements = {k: v[:] for k, v in placements.items()}
        
        for p in pieces_list:
            coord = temp_placements[p].pop(0)
            result.append(coord)
        return result
    else:
        return None