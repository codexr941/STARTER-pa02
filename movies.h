#include <string>
#include <vector>

struct Movie{
  std::string name;
  double rating;
};
class MovieDatabase {
public:
    void loadFromFile(const std::string& filename);

    void printAllMovies() const;

    void processPrefixFile(const std::string& prefixFilename) const;

private:
    std::vector<Movie> movies;

    void sortByName();

    bool queryPrefix(const std::string& prefix, std::string& bestLine) const;

    static bool ratingDescNameAsc(const Movie& a, const Movie& b);

};


