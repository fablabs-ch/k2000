import Vue from 'vue'
import Router from 'vue-router'
import Home from '@/components/Home'
import Settings from '@/components/Settings'
import VueResource from 'vue-resource'

Vue.use(Router)
Vue.use(VueResource)

Vue.http.options.root = 'http://localhost:8080'

export default new Router({
  routes: [
    {
      path: '/',
      name: 'home',
      component: Home
    },
    {
      path: '/settings',
      name: 'settings',
      component: Settings
    }
  ]
})
