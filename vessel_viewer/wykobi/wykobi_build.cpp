/*
(***********************************************************************)
(*                                                                     *)
(* Wykobi Computational Geometry Library                               *)
(* Release Version 0.0.5                                               *)
(* http://www.wykobi.com                                               *)
(* Copyright (c) 2005-2017 Arash Partow, All Rights Reserved.          *)
(*                                                                     *)
(* The Wykobi computational geometry library and its components are    *)
(* supplied under the terms of the General Wykobi License agreement.   *)
(* The contents of the Wykobi computational geometry library and its   *)
(* components may not be copied or disclosed except in accordance with *)
(* the terms of that agreement.                                        *)
(*                                                                     *)
(* URL: https://opensource.org/licenses/MIT                            *)
(*                                                                     *)
(***********************************************************************)
*/

#include "stdafx.h"
#include "wykobi_instantiate.hpp"


int main(void)
{  
	double x1 = -5.0; 
	double y1 = 0.0;
	double x2 = 11.0;
	double y2 = 0.0;
	double cx = 0.0;
	double cy = 0.0;
	double radius = 10.0;
	wykobi::point2d<double> ptn;
	std::vector<wykobi::point2d<double>> out;
	wykobi::intersection_point(x1, y1, x2,y2, cx,  cy, radius, std::back_inserter(out));
	int nSize = out.size();
	for (int i = 0 ; i < nSize; ++i)
	{
		wykobi::point2d<double> ptn = out[i]; 
		int a = 0; 
	}
   return 0;
}
