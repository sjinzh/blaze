//=================================================================================================
/*!
//  \file blaze/math/traits/DMatDVecMultTrait.h
//  \brief Header file for the DMatDVecMultTrait class template
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

#ifndef _BLAZE_MATH_TRAITS_DMATDVECMULTTRAIT_H_
#define _BLAZE_MATH_TRAITS_DMATDVECMULTTRAIT_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/expressions/Forward.h>
#include <blaze/math/typetraits/IsDenseMatrix.h>
#include <blaze/math/typetraits/IsDenseVector.h>
#include <blaze/math/typetraits/IsRowMajorMatrix.h>
#include <blaze/math/typetraits/IsTransposeVector.h>
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
/*!\brief Evaluation of the expression type of a dense matrix/dense vector multiplication.
// \ingroup math_traits
//
// Via this type trait it is possible to evaluate the resulting expression type of a dense
// matrix/dense vector multiplication. Given the row-major dense matrix type \a MT and the
// non-transpose dense vector type \a VT, the nested type \a Type corresponds to the resulting
// expression type. In case either \a MT is not a row-major dense matrix type or \a VT is not
// a non-transpose dense vector type, the resulting data type \a Type is set to \a INVALID_TYPE.
*/
template< typename MT    // Type of the left-hand side row-major dense matrix
        , typename VT >  // Type of the right-hand side non-transpose dense vector
struct DMatDVecMultTrait
{
 private:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   enum { qualified = IsConst<MT>::value || IsVolatile<MT>::value || IsReference<MT>::value ||
                      IsConst<VT>::value || IsVolatile<VT>::value || IsReference<VT>::value };
   /*! \endcond */
   //**********************************************************************************************

   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   typedef SelectType< IsDenseMatrix<MT>::value && IsRowMajorMatrix<MT>::value &&
                       IsDenseVector<VT>::value && !IsTransposeVector<VT>::value
                     , DMatDVecMultExpr<MT,VT>, INVALID_TYPE >  Tmp;

   typedef typename RemoveReference< typename RemoveCV<MT>::Type >::Type  Type1;
   typedef typename RemoveReference< typename RemoveCV<VT>::Type >::Type  Type2;
   /*! \endcond */
   //**********************************************************************************************

 public:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   typedef typename SelectType< qualified, DMatDVecMultTrait<Type1,Type2>, Tmp >::Type::Type  Type;
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************

} // namespace blaze

#endif
