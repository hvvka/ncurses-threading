FROM hvvka/systemy 

COPY ./src/. /workdir
COPY .bash_profile /root/.bashrc

CMD cd p3/project/ && ./compile.sh
