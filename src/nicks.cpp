#include <nicks.h>

// This set of routines keeps track of the nicks and UUID's
bool validate_nick ( std::string S) // returns true if a nick is valid
{
   bool retval = true;
   // first, a nick must not be blank
   if (S.size () == 0 )
   {
     retval = false;
   }
   // check for illegal character
   if (S.find ('@')!=std::string::npos)
   {
     retval = false;
   }
   return retval;
}
