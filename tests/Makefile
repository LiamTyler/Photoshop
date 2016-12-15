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

.PHONY: all golden clean channels passthrough badinput blur edge threshold saturate quantize sharpen chaining compare batch

all: channels passthrough badinput blur edge threshold saturate quantize sharpen chaining compare batch | test_images
	-@rm -f output.txt one.txt zero.txt three.txt

channels: | one.txt zero.txt test_images
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

	@../build/bin/MIA ../resources/test-images/snaily.jpg test_images/snaily-out-pass-throughTest.jpg

	@../build/bin/MIA golden_images/snaily-out-pass-through.jpg -compare test_images/snaily-out-pass-throughTest.jpg > output.txt ;\
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

blur: | one.txt zero.txt test_images

	@echo *Blur 10 Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -blur 10 test_images/peppersBlur10Test.png

	@../build/bin/MIA golden_images/peppersBlur10.png -compare test_images/peppersBlur10Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Blur 10 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Blur 10 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Blur 20 png to jpg Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -blur 20 test_images/peppersBlur20Test.jpg

	@../build/bin/MIA golden_images/peppersBlur20.jpg -compare test_images/peppersBlur20Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Blur 20 png to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Blur 20 png to jpg Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Blur 20 Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -blur 20 test_images/peppersBlur20Test.png

	@../build/bin/MIA golden_images/peppersBlur20.png -compare test_images/peppersBlur20Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Blur 20 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Blur 20 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Blur 0 jpg to png Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -blur 0 test_images/snailyBlur0Test.png

	@../build/bin/MIA golden_images/snailyBlur0.png -compare test_images/snailyBlur0Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Blur 0 jpg to png Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Blur 0 jpg to png Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Blur 5 Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -blur 5 test_images/snailyBlur5Test.jpg

	@../build/bin/MIA golden_images/snailyBlur5.jpg -compare test_images/snailyBlur5Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Blur 5 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Blur 5 Test FAILED on compare" ;\
			fi ;\
		fi

edge: | one.txt zero.txt test_images
	@echo *Edge Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -edge test_images/brainColorEdgeTest.jpg

	@../build/bin/MIA golden_images/brainColorEdge.jpg -compare test_images/brainColorEdgeTest.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Edge Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Edge Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Edge jpg to png Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -edge test_images/brainColorEdgeTest.png

	@../build/bin/MIA golden_images/brainColorEdge.png -compare test_images/brainColorEdgeTest.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Edge jpg to png Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Edge jpg to png Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Edge Bad Input 5 Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -edge 5.0 bad-edge-parameters.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Edge Bad Input 5 was NOT handled correctly; Test FAILED" ;\
		fi

threshold: | one.txt zero.txt test_images

	@echo *Threshold 0 Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0 test_images/peppersThresh0Test.png

	@../build/bin/MIA golden_images/peppersThresh0.png -compare test_images/peppersThresh0Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Threshold 0 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Threshold 0 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Threshold 1 png to jpg Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 1 test_images/peppersThresh1Test.jpg

	@../build/bin/MIA golden_images/peppersThresh1.jpg -compare test_images/peppersThresh1Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Threshold 1 png to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Threshold 1 png to jpg Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Threshold 0.5 png to jpg Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0.5 test_images/peppersThresh5Test.jpg

	@../build/bin/MIA golden_images/peppersThresh5.jpg -compare test_images/peppersThresh5Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Threshold 0.5 png to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Threshold 0.5 png to jpg Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Threshold 0.25 Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0.25 test_images/peppersThresh25Test.png

	@../build/bin/MIA golden_images/peppersThresh25.png -compare test_images/peppersThresh25Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Threshold 0.25 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Threshold 0.25 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Threshold 0.75 png to jpg Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -threshold 0.75 test_images/peppersThresh75Test.jpg

	@../build/bin/MIA golden_images/peppersThresh75.jpg -compare test_images/peppersThresh75Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Threshold 0.75 png to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Threshold 0.75 png to jpg Test FAILED on compare" ;\
			fi ;\
		fi

saturate: | one.txt zero.txt test_images

	@echo *Saturate 1 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 1 test_images/brainColorSat1Test.jpg

	@../build/bin/MIA golden_images/brainColorSat1.jpg -compare test_images/brainColorSat1Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 1 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 1 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate 10 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 10 test_images/brainColorSat10Test.jpg

	@../build/bin/MIA golden_images/brainColorSat10.jpg -compare test_images/brainColorSat10Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 10 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 10 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate 5.5 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 5.5 test_images/brainColorSat55Test.jpg

	@../build/bin/MIA golden_images/brainColorSat55.jpg -compare test_images/brainColorSat55Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 5.5 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 5.5 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate -1 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate -1 test_images/brainColorSatMinus1Test.jpg

	@../build/bin/MIA golden_images/brainColorSatMinus1.jpg -compare test_images/brainColorSatMinus1Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate -1 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate -1 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate -1 Saturate -1 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate -1 -saturate -1 test_images/brainColorSatMinus1Minus1Test.jpg

	@../build/bin/MIA golden_images/brainColorSatMinus1Minus1.jpg -compare test_images/brainColorSatMinus1Minus1Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate -1 Saturate -1 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate -1 Saturate -1 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate -10 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate -10 test_images/brainColorSatMinus10.jpg

	@../build/bin/MIA golden_images/brainColorSatMinus10.jpg -compare test_images/brainColorSatMinus10.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate -10 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate -10 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate 0 jpg to jpg Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 0 test_images/snailyGrayTest.jpg

	@../build/bin/MIA golden_images/snailyGray.jpg -compare test_images/snailyGrayTest.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 0 jpg to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 0 jpg to jpg Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate 0 jpg to png Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 0 test_images/snailyGrayTest.png

	@../build/bin/MIA golden_images/snailyGray.png -compare test_images/snailyGrayTest.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 0 jpg to png Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 0 jpg to png Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate 0 png to png Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -saturate 0 test_images/peppersGrayTest.png

	@../build/bin/MIA golden_images/peppersGray.png -compare test_images/peppersGrayTest.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 0 png to png Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 0 png to png Test FAILED on compare" ;\
			fi ;\
		fi

quantize: | one.txt zero.txt test_images

	@echo *Quantize 2 jpg to png Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -quantize 2 test_images/brainColorQuan2Test.png

	@../build/bin/MIA golden_images/brainColorQuan2.png -compare test_images/brainColorQuan2Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Quantize 2 jpg to png Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Quantize 2 jpg to png Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Quantize 8 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -quantize 8 test_images/brainColorQuan8Test.jpg

	@../build/bin/MIA golden_images/brainColorQuan8.jpg -compare test_images/brainColorQuan8Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Quantize 8 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Quantize 8 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Quantize 100 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -quantize 100 test_images/brainColorQuan100Test.jpg

	@../build/bin/MIA golden_images/brainColorQuan100.jpg -compare test_images/brainColorQuan100Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Quantize 100 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Quantize 100 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Quantize 256 Test has started

	@../build/bin/MIA ../resources/test-images/colorCircles.png -quantize 256 test_images/colorCirclesQuan256Test.png

	@../build/bin/MIA golden_images/colorCirclesQuan256.png -compare test_images/colorCirclesQuan256Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Quantize 256 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Quantize 256 Test FAILED on compare" ;\
			fi ;\
		fi

sharpen: | one.txt zero.txt test_images

	@echo *Sharpen 0 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 0 test_images/brainColorSharp0Test.jpg

	@../build/bin/MIA golden_images/brainColorSharp0.jpg -compare test_images/brainColorSharp0Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Sharpen 0 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Sharpen 0 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Sharpen 10 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 10 test_images/brainColorSharp10Test.jpg

	@../build/bin/MIA golden_images/brainColorSharp10.jpg -compare test_images/brainColorSharp10Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Sharpen 10 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Sharpen 10 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Sharpen 50 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 50 test_images/brainColorSharp50Test.jpg

	@../build/bin/MIA golden_images/brainColorSharp50.jpg -compare test_images/brainColorSharp50Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Sharpen 50 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Sharpen 50 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Sharpen 100 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 100 test_images/brainColorSharp100Test.jpg

	@../build/bin/MIA golden_images/brainColorSharp100.jpg -compare test_images/brainColorSharp100Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Sharpen 100 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Sharpen 100 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Sharpen 10.5 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -sharpen 10.5 test_images/brainColorSharp105Test.jpg

	@../build/bin/MIA golden_images/brainColorSharp105.jpg -compare test_images/brainColorSharp105Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Sharpen 10.5 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Sharpen 10.5 Test FAILED on compare" ;\
			fi ;\
		fi

chaining: | one.txt zero.txt test_images

	@echo *Channel 1 0 0 Sharpen 10 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 1 0 0 -sharpen 10 test_images/brainColorChan100Sharp10Test.jpg

	@../build/bin/MIA golden_images/brainColorChan100Sharp10.jpg -compare test_images/brainColorChan100Sharp10Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Channel 1 0 0 Sharpen 10 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Channel 1 0 0 Sharpen 10 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Saturate 0 Blur 2 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 0 -blur 2 test_images/brainColorGrayBlur2Test.jpg

	@../build/bin/MIA golden_images/brainColorGrayBlur2.jpg -compare test_images/brainColorGrayBlur2Test.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 0 Blur 2 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 0 Blur 2 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Threshold 0.5 Saturate 0 Test has started

	@../build/bin/MIA ../resources/test-images/brainColor.jpg -threshold 0.5 -saturate 0 test_images/brainColorThresh5GrayTest.jpg

	@../build/bin/MIA golden_images/brainColorThresh5Gray.jpg -compare test_images/brainColorThresh5GrayTest.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Saturate 0 Blur 2 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Saturate 0 Blur 2 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Blur 5 Quantize 4 Test has started

	@../build/bin/MIA ../resources/test-images/peppers.png -blur 5 -quantize 4 test_images/peppersBlur5Quan4Test.png

	@../build/bin/MIA golden_images/peppersBlur5Quan4.png -compare test_images/peppersBlur5Quan4Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Blur 5 Quantize 4 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Blur 5 Quantize 4 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Edge Blur 7 Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -edge -blur 7 test_images/snailyEdgeBlur7Test.png

	@../build/bin/MIA golden_images/snailyEdgeBlur7.png -compare test_images/snailyEdgeBlur7Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Edge Blur 7 Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Edge Blur 7 Test FAILED on compare" ;\
			fi ;\
		fi

compare: | one.txt zero.txt test_images

	@echo *Compare jpg to jpg Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -compare ../resources/test-images/snaily.jpg > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Compare jpg to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Compare jpg to jpg Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Compare png to png Test has started

	@../build/bin/MIA ../resources/test-images/colorCircles.png -compare ../resources/test-images/colorCircles.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Compare jpg to jpg Test FAILED to execute" ;\
		else\
			diff output.txt one.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Compare png to png Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Compare Bad Input 17 Test has started

	@../build/bin/MIA ../resources/test-images/snaily.jpg -compare 17 ../resources/test-images/snaily.jpg > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Compare Bad Input 17 was NOT handled correctly; Test FAILED" ;\
		fi
	
batch: | one.txt zero.txt three.txt test_images

	@echo *Batch Edge Test has started

	@../build/bin/MIA ../resources/test-images/mini_brainstack/mrbrain-8bit###.png -edge test_images/brainstack/brainEdge###Test.png

	@../build/bin/MIA golden_images/brainstack/brainEdge###.png -compare test_images/brainstack/brainEdge###Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Batch Edge Test FAILED to execute" ;\
		else\
			diff output.txt three.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Batch Edge Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Batch Quantize 4 Test has started

	@../build/bin/MIA ../resources/test-images/mini_brainstack/mrbrain-8bit###.png -quantize 4 test_images/brainstack/brainQuantize###Test.png

	@../build/bin/MIA golden_images/brainstack/brainQuantize###.png -compare test_images/brainstack/brainQuantize###Test.png > output.txt ;\
		if [ $$? -eq 1 ] ; then\
			echo "Batch Quantize 4 Test FAILED to execute" ;\
		else\
			diff output.txt three.txt > /dev/null ;\
			if [ $$? -ne 0 ] ; then\
				echo "Batch Quantize 4 Test FAILED on compare" ;\
			fi ;\
		fi

	@echo *Batch Bad Input Test has started

	@../build/bin/MIA ../resources/test-images/brainstack/mrbrain-8bit##.png mrbrain-8bit##.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Batch Bad Input was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Batch Bad Output Test has started

	@../build/bin/MIA ../resources/test-images/brainstack/mrbrain-8bit###.png mrbrain-8bit##.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Batch Bad Output was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Batch Bad Input Directory Test has started

	@../build/bin/MIA ../resources/test-images/brainstack/bad-brainstack3/mrbrain-8bit###.png mrbrain-8bit###.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Batch Bad Input Directory was NOT handled correctly; Test FAILED" ;\
		fi

	@echo *Batch Bad Output Name Test has started

	@../build/bin/MIA ../resources/test-images/brainstack/bad-brainstack3/mrbrain-8bit###.png bad-brainstack4.png > output.txt ;\
		if [ $$? -ne 1 ] ; then\
			echo "Batch Bad Output Name was NOT handled correctly; Test FAILED" ;\
		fi


one.txt:
	@echo 1 > one.txt
zero.txt:
	@echo 0 > zero.txt

three.txt:
	@printf "1\n1\n1\n" > three.txt

test_images:
	@mkdir test_images
	@mkdir test_images/brainstack

golden_images:
	@mkdir golden_images
	@mkdir golden_images/brainstack

golden: | golden_images

# Channels
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 0.5 0.5 0 golden_images/brainColorChan550.jpg
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
	
# Chaining
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -channel 1 0 0 -sharpen 10 golden_images/brainColorChan100Sharp10.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -saturate 0 -blur 2 golden_images/brainColorGrayBlur2.jpg
	@../build/bin/MIA ../resources/test-images/brainColor.jpg -threshold 0.5 -saturate 0 golden_images/brainColorThresh5Gray.jpg
	@../build/bin/MIA ../resources/test-images/peppers.png -blur 5 -quantize 4 golden_images/peppersBlur5Quan4.png
	@../build/bin/MIA ../resources/test-images/snaily.jpg -edge -blur 7 golden_images/snailyEdgeBlur7.png

# Pass Through
	@../build/bin/MIA ../resources/test-images/snaily.jpg golden_images/snaily-out-pass-through.jpg

# Batch
	@../build/bin/MIA ../resources/test-images/mini_brainstack/mrbrain-8bit###.png -edge golden_images/brainstack/brainEdge###.png
	@../build/bin/MIA ../resources/test-images/mini_brainstack/mrbrain-8bit###.png -quantize 4 golden_images/brainstack/brainQuantize###.png

clean:
	@rm -rf test_images
	@rm -f output.txt one.txt zero.txt
