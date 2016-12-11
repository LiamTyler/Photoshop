################################################################################
# Name            : Makefile
# Project         : Tests
# Description     : Makefile for Regression Tests
# Creation Date   : 12/7/2016
# Original Author : hende702
#
#  Products:
#  Make Target     Product                  Description
#  ===========     =======                  ===================
#  golden          golden images            generate a set of gold-standard
#  					                        images
#
#  all		       test results	            run all the regression tests
#
################################################################################

golden:
	# Channels
	./build/bin/MIA resources/test_images/brainColor.jpg -channel 5 5 0 tests/golden_images/brainColorChan550.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -channel 1 0.5 0.25 tests/golden_images/brainColorChan1525.png
	./build/bin/MIA resources/test_images/brainColor.jpg -channel 10 10 10 tests/golden_images/brainColorChan101010.jpg
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 0 0 1 tests/golden_images/graphWithoutAlphaChan001.png
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 0 1 0 tests/golden_images/graphWithoutAlphaChan010.png
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 1 0 0 tests/golden_images/graphWithoutAlphaChan100.png
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 1 1 1 tests/golden_images/graphWithoutAlphaChan111.png
	
	# Edge
	./build/bin/MIA resources/test_images/brainColor.jpg -edge tests/golden_images/brainColorEdge.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -edge tests/golden_images/brainColorEdge.png
	
	# Saturate
	./build/bin/MIA resources/test_images/brainColor.jpg -saturate 1 tests/golden_images/brainColorSat1.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -saturate 10 tests/golden_images/brainColorSat10.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -saturate 5.5 tests/golden_images/brainColorSat55.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -saturate -1 tests/golden_images/brainColorSatMinus1.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -saturate -1 -saturate -1 tests/golden_images/brainColorSatMinus1Minus1.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -saturate -10 tests/golden_images/brainColorSatMinus10.jpg
	./build/bin/MIA resources/test_images/snaily.jpg -saturate 0 tests/golden_images/snailyGray.jpg
	./build/bin/MIA resources/test_images/snaily.jpg -saturate 0 tests/golden_images/snailyGray.png
	./build/bin/MIA resources/test_images/peppers.png -saturate 0 tests/golden_images/peppersGray.png
	
	# Quantize
	./build/bin/MIA resources/test_images/brainColor.jpg -quantize 2 tests/golden_images/brainColorQuan2.png
	./build/bin/MIA resources/test_images/brainColor.jpg -quantize 8 tests/golden_images/brainColorQuan8.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -quantize 100 tests/golden_images/brainColorQuan100.jpg
	./build/bin/MIA resources/test_images/colorCircles.png -quantize 256 tests/golden_images/colorCirclesQuan256.png
	
	# Sharpen
	./build/bin/MIA resources/test_images/brainColor.jpg -sharpen 0 tests/golden_images/brainColorSharp0.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -sharpen 10 tests/golden_images/brainColorSharp10.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -sharpen 50 tests/golden_images/brainColorSharp50.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -sharpen 100 tests/golden_images/brainColorSharp100.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -sharpen 10.5 tests/golden_images/brainColorSharp105.jpg
	
	# Threshold
	./build/bin/MIA resources/test_images/peppers.png -threshold 0 tests/golden_images/peppersThresh0.png
	./build/bin/MIA resources/test_images/peppers.png -threshold 1 tests/golden_images/peppersThresh1.jpg
	./build/bin/MIA resources/test_images/peppers.png -threshold 0.5 tests/golden_images/peppersThresh5.jpg
	./build/bin/MIA resources/test_images/peppers.png -threshold 0.25 tests/golden_images/peppersThresh25.png
	./build/bin/MIA resources/test_images/peppers.png -threshold 0.75 tests/golden_images/peppersThresh75.jpg
	
	# Blur
	./build/bin/MIA resources/test_images/peppers.png -blur 10 tests/golden_images/peppersBlur10.png
	./build/bin/MIA resources/test_images/peppers.png -blur 20 tests/golden_images/peppersBlur20.jpg
	./build/bin/MIA resources/test_images/peppers.png -blur 20 tests/golden_images/peppersBlur20.png
	./build/bin/MIA resources/test_images/snaily.jpg -blur 0 tests/golden_images/snailyBlur0.png
	./build/bin/MIA resources/test_images/snaily.jpg -blur 5 tests/golden_images/snailyBlur5.jpg
	
	# Multiple
	./build/bin/MIA resources/test_images/brainColor.jpg -channel 1 0 0 -sharpen 10 tests/golden_images/brainColorChan100Sharp10.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -saturate 0 -blur 2 tests/golden_images/brainColorGrayBlur2.jpg
	./build/bin/MIA resources/test_images/brainColor.jpg -threshold 0.5 -saturate 0 tests/golden_images/brainColorThresh5Gray.jpg
	./build/bin/MIA resources/test_images/peppers.png -blur 5 -quantize 4 tests/golden_images/peppersBlur5Quan4.png
	./build/bin/MIA resources/test_images/snaily.jpg -edge -blur 7 tests/golden_images/snailyEdgeBlur7.png

all: channels

channels:
	@echo Channels 5 5 0 Test has started
	./build/bin/MIA resources/test_images/brainColor.jpg -channel 5 5 0 tests/test_images/brainColorChan550Test.jpg
	ifeq((./build/bin/MIA tests/golden_images/brainColorChan550.jpg -compare tests/test_images/brainColorChan550Test.jpg), 0)
		@echo Channels 5 5 0 Test Failed
	endif

	@echo Channels 1 0.5 0.25 jpg to png Test has started
	./build/bin/MIA resources/test_images/brainColor.jpg -channel 1 0.5 0.25 tests/test_images/brainColorChan1525Test.png
	ifeq((./build/bin/MIA tests/golden_images/brainColorChan1525.png -compare tests/test_images/brainColorChan1525Test.png), 0)
		@echo Channels 1 0.5 0.25 Test Failed
	endif

	@echo Channels 10 10 10 Test has started
	./build/bin/MIA resources/test_images/brainColor.jpg -channel 10 10 10 tests/test_images/brainColorChan101010Test.jpg
	ifeq((./build/bin/MIA tests/golden_images/brainColorChan101010.jpg -compare tests/test_images/brainColorChan101010Test.jpg), 0)
		@echo Channels 10 10 10 Test Failed
	endif

	@echo Channels 0 0 1 Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 0 0 1 tests/test_images/graphWithoutAlphaChan001Test.png
	ifeq((./build/bin/MIA tests/golden_images/graphWithoutAlphaChan001.png -compare tests/test_images/graphWithoutAlphaChan001Test.png), 0)
		@echo Channels 0 0 1 Test Failed
	endif

	@echo Channels 0 1 0 Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 0 1 0 tests/test_images/graphWithoutAlphaChan010Test.png
	ifeq((./build/bin/MIA tests/golden_images/graphWithoutAlphaChan010.png -compare tests/test_images/graphWithoutAlphaChan010Test.png), 0)
		@echo Channels 0 1 0 Test Failed
	endif

	@echo Channels 1 0 0 Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 1 0 0 tests/test_images/graphWithoutAlphaChan100Test.png
	ifeq((./build/bin/MIA tests/golden_images/graphWithoutAlphaChan100.png -compare tests/test_images/graphWithoutAlphaChan100Test.png), 0)
		@echo Channels 1 0 0 Test Failed
	endif

	@echo Channels 1 1 1 Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 1 1 1 tests/test_images/graphWithoutAlphaChan111Test.png
	ifeq((./build/bin/MIA tests/golden_images/graphWithoutAlphaChan111.png -compare tests/test_images/graphWithoutAlphaChan111Test.png), 0)
		@echo Channels 1 1 1 Test Failed
	endif

	@echo Channels -1 1 1 Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel -1 1 1 tests/test_images/graphWithoutAlphaChanMinus111Test.png ; if [ $$? -eq 1 ] ; then @echo Channels -1 1 1 Test Failed ; fi

	@echo Channels 20 20 20 Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 20 20 20 tests/test_images/graphWithoutAlphaChan202020Test.png ; if [ $$? -eq 1 ] ; then @echo Channels 20 20 20 Test Failed ; fi

	@echo Channels 1 1 Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel 1 1 tests/test_images/graphWithoutAlphaChan11Test.png ; if [ $$? -eq 1 ] ; then @echo Channels 1 1 Test Failed ; fi


	@echo Channels one one one Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel one one one tests/test_images/graphWithoutAlphaChanoneoneoneTest.png ; if [ $$? -eq 1 ] ; then @echo Channels one one one Test Failed ; fi

	@echo Channels Test has started
	./build/bin/MIA resources/test_images/graphWithoutAlpha.png -channel tests/test_images/graphWithoutAlphaChanTest.png ; if [ $$? -eq 1 ] ; then @echo Channels Test Failed ; fi














