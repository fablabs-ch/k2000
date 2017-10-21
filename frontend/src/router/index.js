import Vue from 'vue'
import Router from 'vue-router'
import Cocktails from '@/components/Cocktails'
import Settings from '@/components/Settings'

Vue.use(Router)

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
