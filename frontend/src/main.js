// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import Vuetify from 'vuetify'
import VueResource from 'vue-resource'

// Vuetify
import 'vuetify/dist/vuetify.min.css'

import App from './App'
import router from './router'

Vue.use(Vuetify)

Vue.use(VueResource)
Vue.url.options.root = 'http://10.10.0.99:8080/'

Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  data () {
    return {
      // global data store access via vm.$root
      cocktails: [],
      ingredients: {}
    }
  },
  created () {
    const cocktailsDB = require('../static/cocktail.json')
    this.cocktails = cocktailsDB.recipes
    // backup qty to restore after customized version
    this.cocktails.forEach(c => {
      c.items.forEach(i => {
        i.mlOriginal = i.ml
        i.disabled = false
        i.custom = false
      })
    })
    this.ingredients = cocktailsDB.ingredients.reduce((ingredients, i) => {
      ingredients[i.id] = i
      return ingredients
    }, {})
  },
  router,
  template: '<App/>',
  components: { App }
})
