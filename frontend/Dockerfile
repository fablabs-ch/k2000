FROM nginx:alpine

# install curl
RUN apk add --no-cache curl

# create health check
HEALTHCHECK --interval=5s --timeout=2s CMD curl --fail -A "docker-healthcheck-curl/1.0.0" http://localhost:80/ || exit 1

# Configure for angular fallback routes
COPY nginx.conf /etc/nginx/nginx.conf

# Copy built app to wwwroot
COPY dist /usr/share/nginx/html
