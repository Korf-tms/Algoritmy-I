#include<iostream>
#include<vector>

using std::vector;
using Edge = std::pair<int, int>;

vector<Edge> generateSquareCycles(const int numberOfSquares){
    if(numberOfSquares < 1){
        std::cerr << "Does not compute" << std::endl;
        return {};
    }
    vector<Edge> res;
    // 4*n is the most outer square, inner squares have 2*(1 + 2 + ... n - 1) edges
    res.reserve(4*numberOfSquares + numberOfSquares*(numberOfSquares-1));

    // create base square
    /* 0 -> 1
    *  ^    v
    *  3 <- 2
    */
    for(size_t i = 0; i < 4; i++){
        res.emplace_back(i, (i + 1) % 4 );
    }

    int startingPoint = 1; // connecting vertex for new square
    int endingPoint = 3;  // ending vertex for new square
    int startingIndex = 4; // first vertex index in new part
    /* 0 -> 1 -> 4
    *  ^    v    v
    *  3 <- 2    5
    *  ^         v
    *  8 <- 7 <- 6
    */
    // add the rest following the picture above
	// numbering is unreadable but straigthforward
    for(size_t squares=1; squares < numberOfSquares; squares++){
        // first edge
        res.emplace_back(startingPoint, startingIndex);
        //
        for(size_t i = startingIndex; i < (squares+2)*(squares+2)-1; i++ ){
            res.emplace_back(i, i+1);
        }
        // last edge
        res.emplace_back( (squares+2)*(squares+2)-1, endingPoint);

        // update infrastructure for the next square
        startingIndex = (squares+2)*(squares+2);
        startingPoint = startingPoint + 2*squares + 1; // 1, 4, 9, 14
        endingPoint = (squares+2)*(squares+2) - 1;
    }
    return res;
}

vector<Edge> generateLadderCycles(const int numberOfSquares){
    if(numberOfSquares < 1){
        std::cerr << "Does not compute" << std::endl;
        return {};
    }
    vector<Edge> res;
    // 4 for the first square, 3 for all the next
    res.reserve(4 + 3*(numberOfSquares-1));

    // create base square
    for(size_t i = 0; i < 4; i++){
        res.emplace_back(i, (i + 1) % 4 );
    }
    /* 0 -> 1
    *  ^    v
    *  3 <- 2
    */
    // attach smaller squares
    /* 0 -> 1
    *  ^    v
    *  3 <- 2
    *  v    ^
    *  4 -> 5
    *  ^    v
    *  7 <- 6
    */

    int startingIndex = 4; // first index in new square
    int startingPoint = 3; // vertex starting the new cycle
    for(int i = 1; i < numberOfSquares; i++){
        res.emplace_back(startingPoint, startingIndex);
        res.emplace_back(startingIndex, startingIndex+1);
        res.emplace_back(startingIndex+1, startingPoint-1);
        startingIndex += 2;
        startingPoint += 2;
    }
    return res;
}

int main(int argc, char* argv[]){
	if( argc != 3){
		std::cerr << "2 arguments pls\nFirst is name (square or ladder), second is number\n";
		return 1;
	}

    int num = std::stoi(argv[2]);
    std::string opt(argv[1]);
    vector<Edge> graph;

	if( opt == "square"){
		graph = generateSquareCycles(num);
	} else{
		if ( opt == "ladder"){
			graph = generateLadderCycles(num);
		} else {
			std::cerr << opt << "is not regonized, only 'ladder' and 'sqare' are\n";
		}
	}

	// here is probably a good place to apply some prefix to node names
	// to conveniently merge/connect two or more graphs
    for(const auto [from, to] : graph){
        std::cout << from << " " << to << "\n";
    }

    return 0;
}
