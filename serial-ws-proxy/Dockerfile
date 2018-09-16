FROM node
EXPOSE 8080

WORKDIR /app

COPY index.js package.json yarn.lock /app/
RUN yarn install

CMD [ "node", "./index.js" ]
