/// <summary>
/// Represents a matrix of integers with methods to find the maximum value.
/// </summary>


/// <remarks>
/// The matrix is initialized with a given number of rows and columns,
/// and all elements are set to zero. The user can set values for individual
/// elements, and the matrix can calculate the maximum value in the matrix.
/// </remarks>


/// <seealso cref="SetValue(int, int, int)" />
/// <seealso cref="GetMaxValue()" />


public class MaxMatrix
{
    /// <summary>
    /// The number of rows in the matrix.
    /// </summary>
    private int rows;

    /// <summary>
    /// The number of columns in the matrix.
    /// </summary>
    private int columns;

    /// <summary>
    /// The underlying array of integers representing the matrix.
    /// </summary>
    private int[,] matrix;

    /// <summary>
    /// Initializes a new instance of the <see cref="MaxMatrix" /> class.
    /// </summary>
    /// <param name="rows">The number of rows in the matrix.</param>
    /// <param name="columns">The number of columns in the matrix.</param>
    public MaxMatrix(int rows, int columns)
    {
        this.rows = rows;
        this.columns = columns;
        matrix = new int[rows, columns];

        // Initialize all elements to zero
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i, j] = 0;
            }
        }
    }

    /// <summary>
    /// Sets the value of a specific element in the matrix.
    /// </summary>
    /// <param name="row">The row index of the element to set.</param>
    /// <param name="column">The column index of the element to set.</param>
    /// <param name="value">The value to set for the element.</param>
    public void SetValue(int row, int column, int value)
    {
        // Check if the row and column indices are within the bounds of the matrix
        if (row >= 0 && row < rows && column >= 0 && column < columns)
        {
            matrix[row, column] = value;
        }
        else
        {
            throw new IndexOutOfRangeException("Row or column index is out of range.");
        }
    }

    /// <summary>
    /// Gets the maximum value in the matrix.
    /// </summary>
    /// <returns>The maximum value in the matrix.</returns>
    public int GetMaxValue()
    {
        int maxValue = matrix[0, 0];

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (matrix[i, j] > maxValue)
                {
                    maxValue = matrix[i, j];
                }
            }
        }

        return maxValue;
    }
}
