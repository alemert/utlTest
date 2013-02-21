################################################################################
# makefile for test util
################################################################################

MAKE_INCLUDE_PATH=mk.inc

# ------------------------------------------------------------------------------
# Compiler and BIT 
# ------------------------------------------------------------------------------
CC=gcc
BIT = 64

# ------------------------------------------------------------------------------
# debugger
# ------------------------------------------------------------------------------
DBGOPT = -g -D__TDD__

# ------------------------------------------------------------------------------
# sources
# ------------------------------------------------------------------------------
SOURCES = 

LSOWN = libsogen.a

# ------------------------------------------------------------------------------
# main source
# ------------------------------------------------------------------------------
MAIN = main.c

# ------------------------------------------------------------------------------
# BINARY
# ------------------------------------------------------------------------------
BINARY = tutl

# ------------------------------------------------------------------------------
# rollout includes
# ------------------------------------------------------------------------------
ROLLOUT_INC = tutl.h

# ------------------------------------------------------------------------------
# do not change includes
# ------------------------------------------------------------------------------
include $(MAKE_INCLUDE_PATH)/general.modules.mk

# ------------------------------------------------------------------------------
# test is to be adjustet
# ------------------------------------------------------------------------------
TEST = t000
include $(MAKE_INCLUDE_PATH)/test.mk

#test : t000 

#t001 t002 t003 t004 t005 t006

#include $(MAKE_INCLUDE_PATH)/test.mk

#maintest : $(BIN) test/$(BIN_PATH)/t000 test/log/t000.stdout test/log/t000.stderr test/cfg/t000.cmpout test/cfg/t000.cmperr test/log/t000.done
#	$^
