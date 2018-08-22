#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NickTests
#include <boost/test/unit_test.hpp>

#include "nicks.h"

// Note these are just examples of tests.  They
// are not 'correct' for the project requirements
// for what is valid in a nick

BOOST_AUTO_TEST_SUITE ( Nicks )
 
BOOST_AUTO_TEST_CASE ( Validate_empty )
{
    std::string S;
    // an empty string is not valid
    BOOST_CHECK ( !validate_nick ( S ) );
}

BOOST_AUTO_TEST_CASE ( Validate_numbers )
{
    std::string S;
    // a number is not allowed
    S = "1";
    BOOST_CHECK ( !validate_nick ( S ) );
}
 
BOOST_AUTO_TEST_CASE ( Validate_ )
{
    std::string S;
    // an @ is not allowed
    S = "@";
    BOOST_CHECK ( !validate_nick ( S ) );
}

BOOST_AUTO_TEST_CASE ( Validate_good )
{
    std::string S;
    S = "Jim";
    BOOST_CHECK ( validate_nick ( S ) );
    S = "Santiago";
    BOOST_CHECK ( validate_nick ( S ) );
    S = "Malia";
    BOOST_CHECK ( validate_nick ( S ) );
    S = "Bud";
    BOOST_CHECK ( validate_nick ( S ) );
}

BOOST_AUTO_TEST_SUITE_END()

