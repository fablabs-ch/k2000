// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import Vuetify from 'vuetify'
import VueResource from 'vue-resource'
import App from './App'
import router from './router'

// Load font-awesome
import 'font-awesome/css/font-awesome.css'

// Vuetify
import 'vuetify/dist/vuetify.min.css'

Vue.use(Vuetify)

Vue.use(VueResource)
Vue.url.options.root = 'http://10.10.0.99:8080/'

Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  template: '<App/>',
  components: { App }
})
