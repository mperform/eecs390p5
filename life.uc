/**
 *  Simulates Conway's Game of Life on a finite grid.
 */

/**
 *  Runs Conway's Game of Life on a finite (rows x cols) grid for
 *  steps time steps. Initializes the grid such that all cells are
 *  dead excepts those denoted by live_cells_rows and live_cell_cols,
 *  where (live_cells_rows[i], live_cells_cols[i]) denotes the
 *  location of a live cell. Prints the grid after each time step.
 */
void simulate(int rows, int cols, int steps, int[] live_cell_rows,
              int[] live_cell_cols)
  (
   // add local variable declarations here
  ) {
  // your code here
}

/**
 *  Runs a simulation on a 20 x 50 grid. The default number of
 *  timesteps is 20.
 */
void main(string[] args)(int rows, int cols, int steps,
                         int[] live_cell_rows, int[] live_cell_cols) {
  rows = 20;
  cols = 50;
  steps = 20;
  if (args.length > 0) {
    steps = string_to_int(args[0]);
  }
  live_cell_rows = new int[] {
    1, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6,
    6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9
  };
  live_cell_cols = new int[] {
    25, 23, 25, 13, 14, 21, 22, 35, 36, 12, 16, 21, 22, 35, 36, 1, 2,
    11, 17, 21, 22, 1, 2, 11, 15, 17, 18, 23, 25, 11, 17, 25, 12, 16,
    13, 14
  };
  simulate(rows, cols, steps, live_cell_rows, live_cell_cols);
}
