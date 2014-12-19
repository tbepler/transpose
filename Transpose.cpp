
/*
Author: Tristan Bepler (tbepler@gmail.com)
*/


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
        token.clear();
        ss >> token;
        if( !token.empty() ){
            tokens.push_back( token );
        }
    }
    return tokens;
}

struct Transpose{

    vector< vector< string > > entries;
    size_t maxRow;

};

istream& operator>> ( istream& in, Transpose& t ){
    t.entries.clear();
    t.maxRow = 0;
    string line;
    vector<string> row;
    while( getline( in, line ) ){
        row = split( line );
        t.entries.push_back( row );
        if( row.size() > t.maxRow ) t.maxRow = row.size();
    }
    return in;
}

ostream& operator<< ( ostream& out, Transpose& t ){
    //transpose
    vector<string> row;
    for( size_t j = 0 ; j < t.maxRow ; ++j ){
        for( size_t i = 0 ; i < t.entries.size() ; ++i ){
            row = t.entries[i];
            if( j < row.size() ){
                out << row[j];
            }
            out << " ";
        }
        out << endl;
    }
    return out;
}

void usage( ostream& out ){
    out << "Usage: transpose [--help/-h] [--in-place/-i] [FILES] [ < FILE ]" << endl;
    out << "-i\t--in-place\tTransposes the files in place" << endl;
    out << "-h\t--help\tDisplays this help statement" << endl;
}

int main( int argc, const char* argv[] ){

    vector<const char*> files;
    bool inplace = false;
    
    for( int i = 1 ; i < argc ; ++i ){
        string arg(argv[i]);
        if( arg == "--help" || arg == "-h" ){
            usage( cerr );
            return 0;
        }else if( arg == "--in-place" || arg == "-i" ){
            inplace = true;
        }else{
            files.push_back( argv[i] );
        }
    }

    Transpose t;
    if( !files.empty() ){
        fstream fin;
        fstream fout;
        for( size_t i = 0 ; i < files.size() ; ++i ){
            fin.open( files[i], ios::in );
            if( fin.is_open() ){
                fin >> t;
                fin.close();
                if( inplace ){
                    fout.open( files[i], ios::out | ios::trunc );
                    if( fout.is_open() ){
                        fout << t;
                        fout.close();
                    }else{
                        cerr << "Unable to open file for writing: " << files[i] << endl;
                    }
                }else{
                    cout << t;
                }
            }else{
                cerr << "Unable to open file for reading: " << files[i] << endl;
            }
        }
    }else{
        cin >> t;
        cout << t;
    }

}
