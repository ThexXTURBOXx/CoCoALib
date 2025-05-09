// Copyright (c) 2017  John Abbott and Anna M. Bigatti
// Authors: Anna M. Bigatti, Alberto Griggio
// This file is part of the CoCoALib suite of examples.
// You are free to use any part of this example in your own programs.

#include "CoCoA/library.H"

///// first prototype
#include "CoCoA/ExternalLibs-MathSAT.H"

using namespace std;

//----------------------------------------------------------------------
const string ShortDescription =
  "This program shows a prototype for MathSAT communication.\n";

const string LongDescription =
  "This program shows another example for MathSAT communication.    \n"
  "Similar to ex-MathSAT1, also shows the use of verbosity.         \n";

//----------------------------------------------------------------------

namespace CoCoA
{  

  void program()
  {
    GlobalManager CoCoAFoundations;

    cout << ShortDescription << endl;
    cout << LongDescription << endl;
    cout << boolalpha; // so that bools print out as true/false

#ifndef CoCoA_WITH_MATHSAT
    cout << "MathSAT library is not available to CoCoALib." << endl;
#else // MathSAT is available

    ring QQ = RingQQ();

    ring P = NewPolyRing(QQ, symbols("X0,X1"));
    RingElem X0(P,"X0"), X1(P,"X1");

    SetVerbosityLevel(80);
    cout << " ---- VerbosityLevel = " << VerbosityLevel() << endl;    

    cout << " --------------------------------------" << endl
         << " -- add the constraints via polynomials"
         << endl;

    // create a MathSAT environment: E_poly
    MathSAT::env E_poly;
    
    MathSAT::AddLeq0(E_poly, X0-2);
    MathSAT::AddLeq0(E_poly, -X0);
    MathSAT::AddLeq0(E_poly, X1 +3*X0 -2);
    MathSAT::AddLeq0(E_poly, X0 -X1);

    MathSAT::AddNeq0(E_poly, X0);

    matrix sol = NewDenseMat(MathSAT::LinSolve(E_poly));
    cout << "A solution is " << sol << endl;

    cout << " ------------------------------------" << endl
         << " -- add the constraints via matrices"
         << endl;
    
    // create a MathSAT environment: E_mat
    MathSAT::env E_mat;

    matrix M = NewDenseMat(QQ, 4, 3);
    SetEntry(M,0,0, 1);    SetEntry(M,0,1, 0);    SetEntry(M,0,2, -2);
    SetEntry(M,1,0, -1);
    SetEntry(M,2,0, 3);    SetEntry(M,2,1, 1);    SetEntry(M,2,2, -2);
    SetEntry(M,3,0, 1);    SetEntry(M,3,1, -1);
    MathSAT::AddLeq0(E_mat, M);

    M = NewDenseMat(QQ, 1, 3);
    SetEntry(M,0,0, 1);
    MathSAT::AddNeq0(E_mat, M);

    sol = NewDenseMat(MathSAT::LinSolve(E_mat));
    cout << "A solution is " << sol << endl;
    
    //-----------------------------------------------------------------
    cout << " ---------------------------------" << endl
         << " -- mix"
         << endl;
    
    // add a polynomial constraint to E_mat
    MathSAT::AddNeq0(E_mat, 2*X0-1);

    sol = NewDenseMat(MathSAT::LinSolve(E_mat));
    cout << "A solution is " << sol << endl;

#endif // CoCoA_WITH_MATHSAT
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
