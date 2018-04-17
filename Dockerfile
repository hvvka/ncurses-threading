FROM hvvka/systemy 

COPY ./src/. /workdir
COPY .bash_profile /root/.bashrc

CMD cd p2/project/ && ./compile.sh
