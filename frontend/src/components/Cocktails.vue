<template>
  <v-container fluid>
    <v-layout row wrap justify-space-around>
      <v-flex xs12 md5 xl3 v-for="c in $root.cocktails" :key="c.name">
        <cocktail-panel :cocktail="c" @order="handleOrder"></cocktail-panel>
      </v-flex>
    </v-layout>

    <order-dialog :order="order" @close="order = null"></order-dialog>
  </v-container>
</template>

<script>
import CocktailPanel from '@/components/CocktailPanel'
import CocktailLoader from '@/components/CocktailLoader'
import OrderDialog from '@/components/OrderDialog'

export default {
  name: 'cocktails',
  data () {
    return {
      order: null
    }
  },
  methods: {
    handleOrder (order) {
      this.order = order
    },
    add () {
    }
  },
  components: {
    CocktailPanel,
    CocktailLoader,
    OrderDialog
  }
}
</script>

<style>
</style>
