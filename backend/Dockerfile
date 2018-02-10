FROM frolvlad/alpine-oraclejdk8:slim

EXPOSE 8080
EXPOSE 8282

COPY data/ /data
ADD target/*.jar app.jar
RUN sh -c 'touch /app.jar'
ENV JAVA_OPTS=""
ENTRYPOINT [ "sh", "-c", "java $JAVA_OPTS -Djava.security.egd=file:/dev/./urandom -jar /app.jar" ]

HEALTHCHECK --start-period=10s --interval=5s --timeout=3s --retries=2 \
    CMD wget --spider http://localhost:8081/actuator/health
