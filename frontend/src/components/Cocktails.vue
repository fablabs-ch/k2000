<template>
  <v-container fluid>
    <v-layout row wrap justify-space-around>
      <v-flex xs12 md5 xl3 v-for="c in $root.cocktails" :key="c.id">
        <cocktail-panel :cocktail="c" @order="handleOrder"></cocktail-panel>
      </v-flex>
    </v-layout>
    <v-btn
              color="pink"
              dark
              fixed
              bottom
              right
              fab
              @click.native="add"
            >
              <v-icon>add</v-icon>
            </v-btn>
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
      this.$http.post('recipies', {
        name: 'New Cocktail',
        description: '',
        imageUrl: '',
        shakeYourBody: false,
        items: []
      }).then(response => {
        // TODO update reset params from response.data
        this.$root.cocktails.push(response.data)
      }, response => {

      })
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
