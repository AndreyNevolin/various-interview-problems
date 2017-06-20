#include <iostream>

using namespace std;

#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <list>
#include <algorithm>

using std::vector;

class Movie {
private:
    int movieId;
    float rating;
    vector<Movie*> similarMovies; // Similarity is bidirectional

public:
    Movie(int movieId, float rating) {
        this->movieId = movieId;
        this->rating = rating;
    }

    int getId() {
        return movieId;
    }

    float getRating() {
        return rating;
    }

    void addSimilarMovie(Movie* movie) {
        similarMovies.push_back(movie);
        movie->similarMovies.push_back(this);
    }

    vector<Movie *>& getSimilarMovies() {
        return similarMovies;
    }

    static bool compare( Movie *movie1, Movie *movie2) {
        return movie1->getRating() >= movie2->getRating();
    }

    /*
     *     @param movie
     *     @param numTopRatedSimilarMovies
     *                      number of movies we want to return
     *     @return List of top rated similar movies
     */
    static void getMovieRecommendations(Movie& movie, int numTopRatedSimilarMovies, vector<Movie *>& recommendedMovies) {

        if ( numTopRatedSimilarMovies <= 0 ) {
            return;
        }

        unordered_set<int> marker_set;
        list<Movie*> work_list;

        work_list.push_back( &movie);
        marker_set.insert( movie.getId());

        while ( !work_list.empty() ) {
            Movie *current_movie = work_list.front();
            vector<Movie *>& similar_movies = current_movie->getSimilarMovies();

            work_list.pop_front();
            recommendedMovies.push_back( current_movie);

            if ( recommendedMovies.size() == numTopRatedSimilarMovies ) {
                make_heap( recommendedMovies.begin(), recommendedMovies.end(), Movie::compare);
            }

            if ( recommendedMovies.size() > numTopRatedSimilarMovies ) {
                push_heap( recommendedMovies.begin(), recommendedMovies.end(), Movie::compare);
                pop_heap( recommendedMovies.begin(), recommendedMovies.end(), Movie::compare);
                recommendedMovies.pop_back();
            }

            for ( int i = 0; i < similar_movies.size(); i++ )
            {
                Movie *next_movie = similar_movies[i];
                unordered_set<int>::const_iterator elem = marker_set.find( next_movie->getId());

                if ( elem != marker_set.end() )
                    continue;

                marker_set.insert( next_movie->getId());
                work_list.push_back( next_movie);
            }
        }

        if ( recommendedMovies.size() < numTopRatedSimilarMovies ) {
            make_heap( recommendedMovies.begin(), recommendedMovies.end(), Movie::compare);
        }

        /* Return movies sorted in the order of their rating */
        reverse( recommendedMovies.begin(), recommendedMovies.end());

        return;
    }
};

/*
int main()
{
    Movie *movieA = new Movie( 1, 1.2);
    Movie *movieB = new Movie( 2, 2.4);
    Movie *movieC = new Movie( 3, 3.6);
    Movie *movieD = new Movie( 4, 4.8);

    movieA->addSimilarMovie( movieB);
    movieB->addSimilarMovie( movieA);
    movieA->addSimilarMovie( movieC);
    movieC->addSimilarMovie( movieA);
    movieB->addSimilarMovie( movieD);
    movieD->addSimilarMovie( movieB);
    movieC->addSimilarMovie( movieD);
    movieD->addSimilarMovie( movieC);

    vector<Movie *> recommendations;

    Movie::getMovieRecommendations( *movieA, 20, recommendations);

    for ( int i = 0; i < recommendations.size(); i++ )
    {
        cout << recommendations[i]->getId() << " ";
    }

    return 0;
}
*/
