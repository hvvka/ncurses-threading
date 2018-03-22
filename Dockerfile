FROM hvvka/systemy 

COPY ./src/. /workdir
COPY .bash_profile /root/.bashrc

