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

    void queryPrefix(const std::string& prefix) const;

    static bool ratingDescNameAsc(const Movie& a, const Movie& b);

    static std::string makeUpperBoundKey(const std::string& prefix);
};
