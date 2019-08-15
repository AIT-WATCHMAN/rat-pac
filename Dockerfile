FROM mileslucas/ratpac:base
LABEL maintener="Miles Lucas <mdlucas@hawaii.edu>"

USER root

# Watchmakers
RUN git clone https://github.com/ait-watchman/watchmakers
RUN cd watchmakers && \
    ./configure && \
    echo -e "source $(pwd)/env_wm.sh\n" >> /etc/bash.bashrc && \
    cd ../

# Sibyl
RUN git clone https://github.com/ait-watchman/sibyl
RUN source /home/splinter/ratpac/bin/ratpac.sh && \
    cd sibyl && \
    make && \
    cd ../

RUN chown -R splinter /home/splinter
USER splinter

CMD ["/bin/bash"]