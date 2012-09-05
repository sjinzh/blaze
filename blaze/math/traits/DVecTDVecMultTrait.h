//=================================================================================================
/*!
//  \file blaze/math/traits/DVecTDVecMultTrait.h
//  \brief Header file for the DVecTDVecMultTrait class template
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

#ifndef _BLAZE_MATH_TRAITS_DVECTDVECMULTTRAIT_H_
#define _BLAZE_MATH_TRAITS_DVECTDVECMULTTRAIT_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/expressions/Forward.h>
#include <blaze/math/typetraits/IsDenseVector.h>
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
/*!\brief Evaluation of the expression type of a dense vector/transpose dense vector multiplication.
// \ingroup math_traits
//
// Via this type trait it is possible to evaluate the resulting expression type of a dense
// vector/transpose dense vector multiplication (outer product). Given the non-transpose
// dense vector type \a VT1 and the transpose dense vector type \a VT2, the nested type
// \a Type corresponds to the resulting expression type. In case either \a VT1 is not a
// non-transpose dense vector type or \a VT2 is not a transpose dense vector type, the
// resulting \a Type is set to \a INVALID_TYPE.
*/
template< typename VT1    // Type of the left-hand side non-transpose dense vector
        , typename VT2 >  // Type of the right-hand side transpose dense vector
struct DVecTDVecMultTrait
{
 private:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   enum { qualified = IsConst<VT1>::value || IsVolatile<VT1>::value || IsReference<VT1>::value ||
                      IsConst<VT2>::value || IsVolatile<VT2>::value || IsReference<VT2>::value };
   /*! \endcond */
   //**********************************************************************************************

   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   typedef SelectType< IsDenseVector<VT1>::value && !IsTransposeVector<VT1>::value &&
                       IsDenseVector<VT2>::value && IsTransposeVector<VT2>::value
                     , DVecTDVecMultExpr<VT1,VT2>, INVALID_TYPE >  Tmp;

   typedef typename RemoveReference< typename RemoveCV<VT1>::Type >::Type  Type1;
   typedef typename RemoveReference< typename RemoveCV<VT2>::Type >::Type  Type2;
   /*! \endcond */
   //**********************************************************************************************

 public:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   typedef typename SelectType< qualified, DVecTDVecMultTrait<Type1,Type2>, Tmp >::Type::Type  Type;
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************

} // namespace blaze

#endif
