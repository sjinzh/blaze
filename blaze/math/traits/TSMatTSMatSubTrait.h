//=================================================================================================
/*!
//  \file blaze/math/traits/TSMatTSMatSubTrait.h
//  \brief Header file for the TSMatTSMatSubTrait class template
//
//  Copyright (C) 2011 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. This library is free software; you can redistribute
//  it and/or modify it under the terms of the GNU General Public License as published by the
//  Free Software Foundation; either version 3, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
//  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along with a special
//  exception for linking and compiling against the Blaze library, the so-called "runtime
//  exception"; see the file COPYING. If not, see http://www.gnu.org/licenses/.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_TRAITS_TSMATTSMATSUBTRAIT_H_
#define _BLAZE_MATH_TRAITS_TSMATTSMATSUBTRAIT_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/expressions/Forward.h>
#include <blaze/math/typetraits/IsColumnMajorMatrix.h>
#include <blaze/math/typetraits/IsSparseMatrix.h>
#include <blaze/util/InvalidType.h>
#include <blaze/util/SelectType.h>
#include <blaze/util/typetraits/IsConst.h>
#include <blaze/util/typetraits/IsReference.h>
#include <blaze/util/typetraits/IsVolatile.h>
#include <blaze/util/typetraits/RemoveCV.h>
#include <blaze/util/typetraits/RemoveReference.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Evaluation of the expression type of a transpose sparse matrix/transpose sparse matrix
//        subtraction.
// \ingroup math_traits
//
// Via this type trait it is possible to evaluate the resulting expression type of a transpose
// sparse matrix/transpose sparse matrix subtraction. Given the two column-major sparse matrix
// types \a MT1 and \a MT2, the nested type \a Type corresponds to the resulting expression type.
// In case either \a MT1 or \a MT2 is not a column-major sparse matrix, the resulting data type
// \a Type is set to \a INVALID_TYPE.
*/
template< typename MT1    // Type of the left-hand side column-major sparse matrix
        , typename MT2 >  // Type of the right-hand side column-major sparse matrix
struct TSMatTSMatSubTrait
{
 private:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   enum { qualified = IsConst<MT1>::value || IsVolatile<MT1>::value || IsReference<MT1>::value ||
                      IsConst<MT2>::value || IsVolatile<MT2>::value || IsReference<MT2>::value };
   /*! \endcond */
   //**********************************************************************************************

   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   typedef SelectType< IsSparseMatrix<MT1>::value && IsColumnMajorMatrix<MT1>::value &&
                       IsSparseMatrix<MT2>::value && IsColumnMajorMatrix<MT2>::value
                     , TSMatTSMatSubExpr<MT1,MT2>, INVALID_TYPE >  Tmp;

   typedef typename RemoveReference< typename RemoveCV<MT1>::Type >::Type  Type1;
   typedef typename RemoveReference< typename RemoveCV<MT2>::Type >::Type  Type2;
   /*! \endcond */
   //**********************************************************************************************

 public:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   typedef typename SelectType< qualified, TSMatTSMatSubTrait<Type1,Type2>, Tmp >::Type::Type  Type;
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************

} // namespace blaze

#endif
