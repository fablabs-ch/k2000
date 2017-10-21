import Vue from 'vue'
import Router from 'vue-router'
import Cocktails from '@/components/Cocktails'
import Settings from '@/components/Settings'
import VueResource from 'vue-resource'

Vue.use(Router)
Vue.use(VueResource)

Vue.http.options.root = 'http://localhost:8080'

export default new Router({
  routes: [
    {
      path: '/',
      name: 'cocktails',
      component: Cocktails
    },
    {
      path: '/settings',
      name: 'settings',
      component: Settings
    }
  ]
})
