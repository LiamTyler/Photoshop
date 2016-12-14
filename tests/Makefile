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

.PHONY: all golden clean channels passthrough badinput

all: channels passthrough badinput | test_images
	-@rm -f output.txt one.txt zero.txt

channels: | one.txt zero.txt
	@echo *Channels 5 5 0 Test has started

# Create the image we are going to test with
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel .5 .5 0 test_images/brainColorChan550Test.jpg

# First, run -compare. If it returns with a 1, we know the files were invalid, or that
# something went wrong in the c++ code. If it returns 0, we still have to check to
# see what was printed out (saved in output.txt) to see if the images are the same
# or not. That's what the diff does
	@../build/bin/FlashPhoto golden_images/brainColorChan550.jpg -compare test_images/brainColorChan550Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channels 5 5 0 Test FAILED to execute" ;\
		else\
			# the > /dev/null is a trick to not print anything (idk if works on mac)\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channels 5 5 0 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Channels 1 0.5 0.25 jpg to png Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 1 0.5 0.25 test_images/brainColorChan1525Test.png

	@../build/bin/MIA golden_images/brainColorChan1525.png -compare test_images/brainColorChan1525Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channels 1 0.5 0.25 jpg to png Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channels 1 0.5 0.25 jpg to png Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Channels 10 10 10 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 10 10 10 test_images/brainColorChan101010Test.jpg

	@../build/bin/MIA golden_images/brainColorChan101010.jpg -compare test_images/brainColorChan101010Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channels 10 10 10 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channels 10 10 10 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Channels 0 0 1 Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 0 0 1 test_images/graphWithoutAlphaChan001Test.png

	@../build/bin/MIA golden_images/graphWithoutAlphaChan001.png -compare test_images/graphWithoutAlphaChan001Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channels 0 0 1 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channels 0 0 1 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Channels 0 1 0 Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 0 1 0 test_images/graphWithoutAlphaChan010Test.png

	@../build/bin/MIA golden_images/graphWithoutAlphaChan010.png -compare test_images/graphWithoutAlphaChan010Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channels 0 1 0 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channels 0 1 0 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Channels 1 0 0 Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 1 0 0 test_images/graphWithoutAlphaChan100Test.png

	@../build/bin/MIA golden_images/graphWithoutAlphaChan100.png -compare test_images/graphWithoutAlphaChan100Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channels 1 0 0 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channels 1 0 0 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Channels 1 1 1 Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 1 1 1 test_images/graphWithoutAlphaChan111Test.png

	@../build/bin/MIA golden_images/graphWithoutAlphaChan111.png -compare test_images/graphWithoutAlphaChan111Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channels 1 1 1 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channels 1 1 1 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Channels Bad Input -1 1 1 Test has started
# Here is an example of how to test when you know the input is bad.
# Obviously, you can and should change the output messages on all of these
	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel -1 1 1 test_images/graphWithoutAlphaChanMinus111Test.png > output.txt ;\
# Note: The > output.txt above is just to supress the help message that should appear, since\
# we don't need to know what the output is like when we run compare\
		if [ $$? -ne 1 ] ; then\
			echo "Channels Bad Input -1 1 1 was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Channels Bad Input 20 20 20 Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 20 20 20 test_images/graphWithoutAlphaChan202020Test.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Channels Bad Input 20 20 20 was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Channels Bad Input 1 1 Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 1 1 test_images/graphWithoutAlphaChan11Test.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Channels Bad Input 1 1 was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Channels Bad Input one one one Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel one one one test_images/graphWithoutAlphaChanoneoneoneTest.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Channels Bad Input one one one was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Channels Bad Input Test has started

	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel test_images/graphWithoutAlphaChanTest.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Channels Bad Input was NOT handled correctly; Test FAILED" ;\
		fi

passthrough: | one.txt zero.txt
	@echo *Pass Through jpg to jpg Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg test_images/snaily-out-pass-through.jpg

	@../build/bin/MIA ../resources/test-images/snaily.jpg -compare test_images/snaily-out-pass-through.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Pass Through jpg to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Pass Through jpg to jpg Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Pass Through png to png Test has started

	@../build/bin/MIA ../resources/test-images/colorCircles.png test_images/color-circles-pass-through.png

	@../build/bin/MIA ../resources/test-images/colorCircles.png -compare test_images/color-circles-pass-through.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Pass Through png to png Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Pass Through png to png Test FAILED on compare" ;\
			fi ;\
		fi

badinput:
	@echo *Bad Input Extension Test has started

	@../build/bin/MIA ../resources/test-images/snaily.foo test_images/bad-input-extension.jpg > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Bad Input Extension was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Bad Input Does Not Exist Test has started

	@../build/bin/MIA does/not/exist.jpg test_images/input-does-not-exist.jpg > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Bad Input Does Not Exist was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Bad Output Extension Test has started

	@../build/bin/MIA ../resources/test-images/colorCircles.png test_images/color-circles.foo > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Bad Output Extension was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Bad Output Does Not Exist Test has started

	@../build/bin/MIA ../resources/test-images/colorCircles.png does/not/exist.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Bad Output Does Not Exist was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Bad Input File Missing Test has started

	@../build/bin/MIA -sharpen 5.0 test_images/missing-input-file.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Bad Input File Missing was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Bad Output File Missing Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 5.0 > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Bad Output File Missing was NOT handled correctly; Test FAILED" ;\
		fi

blur: | one.txt zero.txt

	@echo *Blur 10 Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -blur 10 test_images/peppersBlur10Test.png

	@../build/bin/MIA golden_images/peppersBlur10.png -compare test_images/peppersBlur10Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Pass Through jpg to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Pass Through jpg to jpg Test FAILED on compare" ;\
			fi ;\
		fi

	@../build/bin/MIA ../resources/test-images/peppers.png -blur 10 golden_images/peppersBlur10.png
	@../build/bin/MIA ../resources/test-images/peppers.png -blur 20 golden_images/peppersBlur20.jpg
	@../build/bin/MIA ../resources/test-images/peppers.png -blur 20 golden_images/peppersBlur20.png
	@../build/bin/MIA ../resources/test-images/snaily.jpg -blur 0 golden_images/snailyBlur0.png
	@../build/bin/MIA ../resources/test-images/snaily.jpg -blur 5 golden_images/snailyBlur5.jpg

one.txt:
	@echo 1 > one.txt
zero.txt:
	@echo 0 > zero.txt

test_images:
	@mkdir test_images

golden_images:
	@mkdir golden_images

golden: | golden_images

	# Channels
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 5 5 0 golden_images/brainColorChan550.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 1 0.5 0.25 golden_images/brainColorChan1525.png
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 10 10 10 golden_images/brainColorChan101010.jpg
	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 0 0 1 golden_images/graphWithoutAlphaChan001.png
	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 0 1 0 golden_images/graphWithoutAlphaChan010.png
	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 1 0 0 golden_images/graphWithoutAlphaChan100.png
	@../build/bin/MIA ../resources/test-images/graphWithoutAlpha.png -channel 1 1 1 golden_images/graphWithoutAlphaChan111.png
	
	# Edge
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -edge golden_images/brainColorEdge.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -edge golden_images/brainColorEdge.png
	
	# Saturate
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 1 golden_images/brainColorSat1.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 10 golden_images/brainColorSat10.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 5.5 golden_images/brainColorSat55.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate -1 golden_images/brainColorSatMinus1.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate -1 -saturate -1 golden_images/brainColorSatMinus1Minus1.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate -10 golden_images/brainColorSatMinus10.jpg
	@../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 0 golden_images/snailyGray.jpg
	@../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 0 golden_images/snailyGray.png
	@../build/bin/MIA ../resources/test-images/peppers.png -saturate 0 golden_images/peppersGray.png
	
	# Quantize
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -quantize 2 golden_images/brainColorQuan2.png
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -quantize 8 golden_images/brainColorQuan8.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -quantize 100 golden_images/brainColorQuan100.jpg
	@../build/bin/MIA ../resources/test-images/colorCircles.png -quantize 256 golden_images/colorCirclesQuan256.png
	
	# Sharpen
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 0 golden_images/brainColorSharp0.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 10 golden_images/brainColorSharp10.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 50 golden_images/brainColorSharp50.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 100 golden_images/brainColorSharp100.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 10.5 golden_images/brainColorSharp105.jpg

	# Threshold
	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0 golden_images/peppersThresh0.png
	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 1 golden_images/peppersThresh1.jpg
	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0.5 golden_images/peppersThresh5.jpg
	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0.25 golden_images/peppersThresh25.png
	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0.75 golden_images/peppersThresh75.jpg
	
	# Blur
	@../build/bin/MIA ../resources/test-images/peppers.png -blur 10 golden_images/peppersBlur10.png
	@../build/bin/MIA ../resources/test-images/peppers.png -blur 20 golden_images/peppersBlur20.jpg
	@../build/bin/MIA ../resources/test-images/peppers.png -blur 20 golden_images/peppersBlur20.png
	@../build/bin/MIA ../resources/test-images/snaily.jpg -blur 0 golden_images/snailyBlur0.png
	@../build/bin/MIA ../resources/test-images/snaily.jpg -blur 5 golden_images/snailyBlur5.jpg
	
	# Multiple
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 1 0 0 -sharpen 10 golden_images/brainColorChan100Sharp10.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 0 -blur 2 golden_images/brainColorGrayBlur2.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -threshold 0.5 -saturate 0 golden_images/brainColorThresh5Gray.jpg
	@../build/bin/MIA ../resources/test-images/peppers.png -blur 5 -quantize 4 golden_images/peppersBlur5Quan4.png
	@../build/bin/MIA ../resources/test-images/snaily.jpg -edge -blur 7 golden_images/snailyEdgeBlur7.png

clean:
	@rm -rf test_images
	@rm -f output.txt one.txt zero.txt
