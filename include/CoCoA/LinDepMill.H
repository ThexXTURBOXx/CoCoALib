#ifndef CoCoA_LinDepMill_H
#define CoCoA_LinDepMill_H

//   Copyright (c)  2018  John Abbott,  Anna M. Bigatti

//   This file is part of the source of CoCoALib, the CoCoA Library.
//
//   CoCoALib is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   CoCoALib is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with CoCoALib.  If not, see <http://www.gnu.org/licenses/>.

#include "CoCoA/ring.H"

#include <iostream>
#include <memory>
//using std::unique_ptr;
#include <vector>
//using std::vector;

namespace CoCoA
{

  class ring;             // fwd decl -- defined in ring.H
  class RingElem;         // fwd decl -- defined in ring.H
  class LinDepMillBase;   // fwd decl -- defined in LinDepMill.C

  class LinDepMill
  {
  public:
    LinDepMill(const ring& k, long dim);
    bool myAppendVec(const std::vector<RingElem>& v);
    const std::vector<RingElem>& myLinReln() const;
    ~LinDepMill(); // >>> WARNING <<<  dtor **must** be out of line (because type of data mem is only partially known)
  
  private:
    std::unique_ptr<LinDepMillBase> myImpl;
    // ring myRing;
    // int myVecLen;
    // std::vector< std::vector<RingElem> > myM;
    // std::vector< std::vector<RingElem> > myRowRepr;
    // std::vector<int> myColIndices;
    // std::vector<RingElem> myLinRelnValue;
  };


} // end of namespace CoCoA

#endif
