#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Thu Nov  7 18:42:31 2019 @author(s): MSO
steering wheel torque simplified
"""
from numpy import array, inner
from numpy.linalg import norm

A = array([1,1,1])
B = array([2,2,0])

k = B-A
k = k/ norm(k)


M_z = array([0,0,20]) #Nm
M_kpi = inner(k,M_z)

r_srt = 12e-3 #m
M_steer = 10 #Nm

r_pat = M_kpi/M_steer * r_srt