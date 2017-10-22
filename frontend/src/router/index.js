import Vue from 'vue'
import Router from 'vue-router'
import Cocktails from '@/components/Cocktails'
import Ingredients from '@/components/Ingredients'
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
      path: '/ingredients',
      name: 'ingredients',
      component: Ingredients
    },
    {
      path: '/settings',
      name: 'settings',
      component: Settings
    }
  ]
})
