// Copyright (c) 2016  John Abbott,  Anna M. Bigatti
// This file is part of the CoCoALib suite of examples.
// You are free to use any part of this example in your own programs.

#include "CoCoA/library.H"

using namespace std;

//----------------------------------------------------------------------
const string ShortDescription =
  "This example illustrates how to create an algebraic extension of a finite \n"
  "field, and how to obtain its generator.                                   \n";

const string LongDescription =
  "This example illustrates how to create an algebraic extension of a finite \n"
  "field, and how to obtain its generator.  We use the (group) generator to  \n"
  "run through all the elements of the finite field.                         \n";

//----------------------------------------------------------------------

namespace CoCoA
{

  void program()
  {
    GlobalManager CoCoAFoundations;

    cout << ShortDescription << endl;
    cout << boolalpha; // so that bools print out as true/false

    const int p = 3;
    const int ExtnDeg = 2;

    ring FFq = NewRingFqLog(p,ExtnDeg);
    const long card = SmallPower(p, ExtnDeg);
    cout << FFq << " is a finite field of char " << p << " and cardinality " << card << endl;
    cout << "The extension is generated by " << gens(DefiningIdeal(FFq))[0] << endl;
    cout << "Its elements are:" << endl;

    cout << zero(FFq) << endl;
    // The extn generator is actually a GROUP generator, so it is easy to run through all elements.
    ring FFpx = BaseRing(FFq);
    RingElem x = indet(FFpx,0);
    RingElem gen = QuotientingHom(FFq)(x);
    for (int i=0; i < card-1; ++i)
      cout << power(gen,i) << endl;
  }

} // end of namespace CoCoA

//----------------------------------------------------------------------
// Use main() to handle any uncaught exceptions and warn the user about them.
int main()
{
  try
  {
    CoCoA::program();
    return 0;
  }
  catch (const CoCoA::ErrorInfo& err)
  {
    cerr << "***ERROR***  UNCAUGHT CoCoA error";
    ANNOUNCE(cerr, err);
  }
  catch (const std::exception& exc)
  {
    cerr << "***ERROR***  UNCAUGHT std::exception: " << exc.what() << endl;
  }
  catch(...)
  {
    cerr << "***ERROR***  UNCAUGHT UNKNOWN EXCEPTION" << endl;
  }

  CoCoA::BuildInfo::PrintAll(cerr);
  return 1;
}
