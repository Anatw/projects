# Build has three steps:
# Remove all cached pyc files, they don't work well with containers
# Create a volume to mount the source code into
# Build the docker image
build:
	find . -name "*.pyc" -delete
	docker volume create src
	docker build --rm -t regex_search_tool:1.0 .

run:
	# Run the docker image in interactive mode, connected to the source volume
	docker run -v /home/anat/anat-wax/RedHat/regex_search_tool:/tests/src -it regex_search_tool:1.0


.PHONY: clean
clean:
	rm *.o output
	docker rm $(docker ps -a -q)
	#docker rmi $(docker images | grep "^<none>" | awk "{print $3}")
