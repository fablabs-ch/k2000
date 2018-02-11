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
Vue.url.options.root = '/api/'

Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  data () {
    return {
      // global data store access via vm.$root
      cocktails: [],
      ingredients: {},
      snackbar: false,
      snacktext: ''
    }
  },
  created () {
    this.$http.get('ingredients').then(response => {
      const serverIngredients = response.data || []
      this.ingredients = serverIngredients.reduce((ingredients, i) => {
        ingredients[i.id] = i
        return ingredients
      }, {})
      this.$http.get('recipies').then(response => {
        this.cocktails = response.data || []
        // backup qty to restore after customized version
        this.cocktails.forEach(c => {
          c.itemsOriginal = c.items.map(i => {
            i.mlOriginal = i.ml
            i.disabled = false
            i.custom = false
            return i
          })
        })
      })
    })
  },
  methods: {
    notify (message) {
      this.snacktext = message
      this.snackbar = true
    }
  },
  router,
  template: '<App/>',
  components: { App }
})
