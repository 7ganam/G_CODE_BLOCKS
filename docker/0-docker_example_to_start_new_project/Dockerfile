FROM ubuntu
RUN apt-get update; 

#to build an image out of this dockerfile 
#     docker build -t <image name> .
#ex: #docker build -t bare_meteor  .

#to make a container out of image:
#    docker container run -it --name <container name>  -p <portno_in_host:portno_in_container> -v "< work_dir_in_host : work_dir_in_container >  <image name>
#ex: docker container run -it --name bare_linux -p 3000:3000 -v "$(pwd)"/dock:/dock  bare_meteor

#to start the container after exit
# docker start <container name> -i
# docker start meteor_2 -i
