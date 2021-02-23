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
	# Build the docker image
	docker build -t redhatenv:1.0  .

run:
	# Run the docker image
	docker run -t redhatenv:1.0


.PHONY: clean
clean:
	rm *.o output
	docker rm $(docker ps -a -q)
	#docker rmi $(docker images | grep "^<none>" | awk "{print $3}")
