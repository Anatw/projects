build:
 	# Remove all cached pyc files, they don't work well with containers
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
