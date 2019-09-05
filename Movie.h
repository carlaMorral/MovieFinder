#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;


class Movie {
    
public:
    Movie();
    Movie(int, string, float);
    Movie(const Movie& orig);
    virtual ~Movie();
    
    // Consultors
    int getMovieID() const;
    string getTitle() const;
    float getRating() const;
    string getRating(int) const;
    string toString() const;
    
    // Modificadors
    void setMovieID(int);
    void setTitle(string);
    void setRating(float);
    
    // Altres
    friend ostream& operator<<(ostream&, const Movie&);
    
private:
    int movieID;
    string title;
    float rating;
    
};


#endif /* MOVIE_H */
