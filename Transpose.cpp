
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

vector<string> split( const string& line ){
    stringstream ss( line );
    vector<string> tokens;
    string token;
    while( !ss.eof() ){
        ss >> token;
        tokens.push_back( token );
    }
    return tokens;
}

void transpose( istream& in, ostream& out ){
    string line;
    vector< vector<string> > entries;
    vector<string> row;
    size_t maxLen = 0;
    while( getline( in, line ) ){
        row = split( line );
        entries.push_back( row );
        if( row.size() > maxLen ) maxLen = row.size();
    }

    //transpose
    for( size_t j = 0 ; j < maxLen ; ++j ){
        for( size_t i = 0 ; i < entries.size() ; ++i ){
            row = entries[i];
            if( j < row.size() ) out << row[j];
            out << " ";
        }
        out << endl;
    }

}

int main( int argc, const char* argv[] ){
    
    for( int i = 1 ; i < argc ; ++i ){
        string arg(argv[i]);
        if( arg == "--help" || arg == "-h" ){
            cerr << "Usage: transpose [FILES] [ < FILE ]" << endl;
            return 0;
        }
    }


    if( argc > 1 ){
        for( int i = 1 ; i < argc ; ++i ){
            ifstream in( argv[i] );
            if( in.is_open() ){
                transpose( in, cout );
                in.close();
            }else{
                cerr << "Unable to open file: " << argv[i] << endl;
            }
        }
    }else{
        transpose( cin, cout );
    }

}
