#ifndef assign_and_process
#define assign_and_process



namespace determinant{

    long double d1(std::vector<std::vector<long double>> numbers){
        std::cout << "\n\n" << 1/numbers[0][0];
    }

    long double d2(std::vector<std::vector<long double>> numbers){
        int ad = numbers[0][0] * numbers[1][1];
        int bc = numbers[1][0] * numbers[0][1];
        return ad - bc;
    }

    long double d3(const std::vector<std::vector<long double>> numbers){

        long double det =
        numbers[0][0] * (numbers[1][1] * numbers[2][2] - numbers[1][2] * numbers[2][1]) -
        numbers[0][1] * (numbers[1][0] * numbers[2][2] - numbers[1][2] * numbers[2][0]) +
        numbers[0][2] * (numbers[1][0] * numbers[2][1] - numbers[1][1] * numbers[2][0]);
        return det;
    }
}





namespace adjoint{

    //if i am making a matrix return in the statement then the type of function should also matvchit
    std::vector<std::vector<long double>> d2(std::vector<std::vector<long double>> numbers) {
        // Check if the input matrix is 2x2 . if i wont do this then matrix doesnt have a defined size . will cause bad alloc
        if (numbers.size() != 2 || numbers[0].size() != 2 || numbers[1].size() != 2) {
            std::cerr << "Error: Input matrix is not 2x2." << std::endl;
            return {}; // Return an empty matrix or handle the error accordingly
        }

        // Calculate the adjoint of the 2x2 matrix
        long double d = numbers[1][1];
        numbers[1][1] = numbers[0][0];
        numbers[0][0] = d;

        numbers[0][1] = -numbers[0][1];
        numbers[1][0] = -numbers[1][0];

        return numbers;
    }


    std::vector<std::vector<long double>> transpose(const std::vector<std::vector<long double>>& matrix);

    std::vector<std::vector<long double>> cofactorMatrix(const std::vector<std::vector<long double>>& matrix, int row, int col) {
        int n = matrix.size();
        std::vector<std::vector<long double>> cofactor(n - 1, std::vector<long double>(n - 1));

        for (int i = 0, r = 0; i < n; ++i) {
            if (i == row) continue;
            for (int j = 0, c = 0; j < n; ++j) {
                if (j == col) continue;
                cofactor[r][c] = matrix[i][j];
                ++c;
            }
            ++r;
        }

        return cofactor;
    }

    std::vector<std::vector<long double>> d3(const std::vector<std::vector<long double>>& matrix) {
        int n = matrix.size();
        std::vector<std::vector<long double>> adjoint(n, std::vector<long double>(n));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::vector<std::vector<long double>> cofactor = cofactorMatrix(matrix, i, j);
                adjoint[i][j] = (i + j) % 2 == 0 ? determinant::d2(cofactor) : -determinant::d2(cofactor);
            }
        }

        // Transpose the adjoint matrix
        std::vector<std::vector<long double>> transposed = transpose(adjoint);
        return transposed;
    }

    std::vector<std::vector<long double>> transpose(const std::vector<std::vector<long double>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        std::vector<std::vector<long double>> transposed(m, std::vector<long double>(n));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                transposed[j][i] = matrix[i][j];
            }
        }

        return transposed;
    }

}


void printing(std::vector<std::vector<long double>>& numbers, long double determinant) {
    if (determinant == 0.0) {
        std::cout << "Error: Determinant is zero, cannot perform division." << std::endl;
        return;
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        for (size_t j = 0; j < numbers[i].size(); ++j) {
            numbers[i][j] /= determinant;
        }
    }

    // Open the file in append mode
    std::ofstream outputFile("writer.txt", std::ios::app);

    // Check if the file is opened successfully
    if (outputFile.is_open()) {
        // Write the 2D vector elements to the file
        outputFile << "\n\nANSWER \n";
        for (const auto& row : numbers) {
            for (const auto& val : row) {
                outputFile << val << " ";
            }
            outputFile << "\n";
        }

        // Close the file
        outputFile.close();

        std::cout << "Data written to file successfully." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}





int assign(int rowSize,std::vector<std::vector<long double>> numbers){
        
    if(rowSize == 0){
        std::cout << "No matrix";
        return 0;
    }

    if(rowSize == 1){
        determinant::d1(numbers);
        return 0;
    }

    if(rowSize == 2){
        std::vector<std::vector<long double>> result = adjoint::d2(numbers);
        long double determinant = determinant::d2(numbers);
        std::cout << "det = " << determinant << "\n\n";
        printing(result,determinant);
        return 0;
    }

    if(rowSize == 3){
        long double determinant = determinant::d3(numbers);
        std::vector<std::vector<long double>> result = adjoint::d3(numbers);
        printing(result,determinant);
    }

    else{std::cout << "No pre";}
    // elif(rowSize == 1){}
}


#endif // FILE_READER_H
