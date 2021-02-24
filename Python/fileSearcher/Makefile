# #every time that main.o or message.o changes, the line below will be executed:
# output: main.o message.o
# 	g++ main.o message.o -o output
#
# #when there is a change in the main.cpp file - execute the line bellow (compile main.cpp) - this will compile into a main.o file, which in turn will trigger the output to execute it's command:
# main.o: main.cpp
# 	g++ -c main.cpp
#
# message.o: message.cpp message.h
# 	g++ -c message.cpp
#
# # build the container for tests
# build:

# run the tests inside the container
build:
 	# Remove all cached pyc files, they don't play nice with the containers
	find . -name "*.pyc" -delete
	# create a volume to mount the source code into
	docker volume create src
	# Build the docker image
	docker build --rm -t redhatenv:1.0  .

run:
	# Run the docker image in interactive mode, connected to the source volume
	docker run -v /home/anat/anat-wax/Python/fileSearcher/src:/tests/src -it redhatenv:1.0


.PHONY: clean
clean:
	rm *.o output
	docker rm $(docker ps -a -q)
	#docker rmi $(docker images | grep "^<none>" | awk "{print $3}")
